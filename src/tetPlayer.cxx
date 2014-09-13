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
		tetMove move;
		keySender->swapHold();
		bool hold = tetAi::chooseMove(*game, getNextPiece(), &move);
		if (hold)
			keySender->swapHold();
		keySender->dropPiece(move.direction,move.x);
		cout << "drop " << move.piece << " rotated right " << move.direction << " in column " << move.x << endl;
		this_thread::sleep_for(chrono::milliseconds(3000));
	}
}

void tetPlayer::go()
{
	//play 1 game for now
	//while(true)
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