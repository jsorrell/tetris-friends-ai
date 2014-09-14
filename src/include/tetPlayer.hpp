#ifndef __TET_PLAYER_H__
#define __TET_PLAYER_H__

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <vector>
#include "tetAi.hpp"
#include "tetCore.hpp"
#include "tetKeySender.hpp"
#include "tetGameInfo.hpp"
#include "tetConstants.hpp"

namespace Tetris {
class tetPlayer
{
public:
	tetPlayer(const string interface);
	~tetPlayer();
	void go();

private:
	void playGame() const;
	tetPiece getNextPiece() const;
	void gameStartedCallback();
	void gameEndedCallback();
	tetGame *game;
	tetGameInfo *info;
	tetKeySender *keySender;
	bool gameStarted = false;
	int gamePid;
	vector<tetPiece> pieceBuf;
};
}
#endif