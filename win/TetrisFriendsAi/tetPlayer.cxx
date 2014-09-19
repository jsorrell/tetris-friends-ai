#include <windows.h>
#include <sys/types.h>
#include <vector>
#include "tetCore.hpp"
#include <signal.h>
#include "tetPlayer.hpp"
#include "tetAi.hpp"
#include "tetConstants.hpp"
#include "tetKeySender.hpp"
#include "tetGameInfo.hpp"

using namespace std;
using namespace Tetris;

struct tetPlayer::impl
{

static DWORD WINAPI playGame(LPVOID t)
{
  unique_ptr<impl>* that = ((unique_ptr<impl>*)t);
	while ((*that)->gameRunning) {
		tetPiece nextPiece = (*that)->getNextPiece();
    tetMove move;
    bool hold = tetAi::chooseMove(*(*that)->game, nextPiece, &move);
		if (hold){
      (*that)->keySender->swapHold();
      (*that)->game->setHoldPiece(nextPiece);
		}
		cout << "drop " << move.piece << " rotated right " << move.direction << " in column " << move.x << endl;
    int linesCleared = (*that)->game->dropPiece(move);
    (*that)->game->board->printBoard();
    (*that)->keySender->dropPiece(move.direction, move.x);
    if ((*that)->game->board->toppedOut) {
			cout << "Topped Out" << endl;
			return 1;
		}
    if (linesCleared)
      Sleep(tetConstants::pause_after_clear_ms);
	}
  return 0;
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
  //FIXME
  //exit(0);
	game->reset();
	gameStarted = false;
  gameRunning = false;
	pieceBuf = {};
}
tetGame *game;
tetGameInfo *info;
tetKeySender *keySender;
bool gameStarted = false;
std::vector<tetPiece> pieceBuf;
HANDLE gameThread;
bool gameRunning; //for controlling game thread
};

tetPlayer::tetPlayer(string intr) : pimpl(new impl)
{
	pimpl->info = new tetGameInfo(intr);
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
		//start game thread
    DWORD gameThreadId;
    pimpl->gameRunning = true;
    pimpl->gameThread = CreateThread(
      NULL,                   // default security attributes
      0,                      // use default stack size  
      &impl::playGame,        // thread function name
      &pimpl,                 // argument to thread function 
      0,                      // use default creation flags 
      &gameThreadId);         // returns the thread identifier

		pimpl->info->captureEnd();
		//FIXME
		pimpl->gameEndedCallback();
	}
}