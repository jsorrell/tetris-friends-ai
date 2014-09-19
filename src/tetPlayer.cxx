#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <thread>
#include <chrono>
#include <signal.h>
#include "tetCore.hpp"
#include "tetPlayer.hpp"
#include "tetAi.hpp"
#include "tetConstants.hpp"
#include "tetKeySender.hpp"
#include "tetGameInfo.hpp"

using namespace std;
using namespace Tetris;

struct tetPlayer::impl
{

void playGame() const
{
	while (true) {
		tetPiece nextPiece = getNextPiece();
		tetMove move;
		bool hold = tetAi::chooseMove(*game, nextPiece, &move);
		if (hold){
			keySender->swapHold();
			game->setHoldPiece(nextPiece);
		}
		cout << "drop " << move.piece << " rotated right " << move.direction << " in column " << move.x << endl;
		int linesCleared = game->dropPiece(move);
		game->board->printBoard();
		keySender->dropPiece(move.direction,move.x);
		if (game->board->toppedOut) {
			cout << "Topped Out" << endl;
			exit(0);
		}
		if (linesCleared)
			this_thread::sleep_for(chrono::milliseconds(tetConstants::pause_after_clear_ms));
	}
}

tetPiece getNextPiece() const
{
	static vector<tetPiece>pieceBuf = {};
	if (!gameStarted) {
		cerr << "Don't know pieces until game starts\n";
		tetPiece piece("Z");
		return piece;
	}
	if (pieceBuf.empty()) {
		pieceBuf = info->getNextBag();
	}
	tetPiece nextPiece = pieceBuf.front();
	pieceBuf.erase(pieceBuf.begin());

	return nextPiece;
}

void gameStartedCallback()
{
	gameStarted = true;
}

void gameEndedCallback()
{
	kill(gamePid,SIGTERM);
	game->reset();
	gameStarted = false;
	pieceBuf = {};
	cout << "Game Over\n";
}
tetGame *game;
tetGameInfo *info;
tetKeySender *keySender;
bool gameStarted = false;
int gamePid;
std::vector<tetPiece> pieceBuf;
};

tetPlayer::tetPlayer(string interface) : pimpl(new impl)
{
	pimpl->info = new tetGameInfo(interface);
	pimpl->game = new tetGame(10,20);
	pimpl->keySender = new tetKeySender();
}

tetPlayer::~tetPlayer()
{
	pimpl.reset();
	pimpl.release();
}

void tetPlayer::go()
{
	//play 1 game for now
	while(true){
		pimpl->info->captureStart();
		//FIXME:
		pimpl->gameStartedCallback();
		if(!(pimpl->gamePid = fork())) {
			pimpl->playGame();
		}
		pimpl->info->captureEnd();
		//FIXME
		pimpl->gameEndedCallback();
	}
}