#include "tetPlayer.hpp"

using namespace Tetris;

tetPlayer::tetPlayer(string interface)
{
	info = new tetGameInfo(interface);
	game = new tetGame(10,20);
	keySender = new tetKeySender();
}

tetPlayer::~tetPlayer()
{
}

tetPiece tetPlayer::getNextPiece() const
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

void tetPlayer::gameStartedCallback()
{
	gameStarted = true;
}

void tetPlayer::gameEndedCallback()
{
	kill(gamePid,SIGTERM);
	game->reset();
	gameStarted = false;
	pieceBuf = {};
}

void tetPlayer::playGame() const
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
		game->dropPiece(move);
		game->board->printBoard();
		keySender->dropPiece(move.direction,move.x);
		if (game->board->toppedOut) {
			cout << "Topped Out" << endl;
			exit(0);
		}
	}
}

void tetPlayer::go()
{
	//play 1 game for now
	while(true){
		info->captureStart();
		//FIXME:
		gameStartedCallback();
		if(!(gamePid = fork())) {
			playGame();
		}
		info->captureEnd();
		//FIXME
		gameEndedCallback();
	}
}