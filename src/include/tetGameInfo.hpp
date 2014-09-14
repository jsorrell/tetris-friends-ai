#ifndef __TET_GAME_INFO_H__
#define __TET_GAME_INFO_H__

#include <cstdlib>
#include <string>
#include <tins/tins.h>
#include <regex>
#include <vector>
#include <thread>
#include "tetConstants.hpp"
#include "tetCore.hpp"

namespace Tetris {

class tetRandomPieceGen {
public:
  tetRandomPieceGen(int seed);
  int getNextRandom();

private:
  int mRand1;
  int mRand2;
  int mRandBuffer[17];
  int mSeed;
};

class tetGameInfo {
public:
	tetGameInfo(string adaptor);
	tetGameInfo(int seed);
	~tetGameInfo();
	void captureStart();
	void captureStartAsync();
	void captureEnd();
	void captureEndAsync();
	void captureLines();
	void captureLinesAsync();
	void registerLinesSentCallback(void(*callback)(const int numLines));
	void registerLinesReceivedCallback(void(*callback)(const int numLines));
	void registerGameStartedCallback(void(*callback)());
	void registerGameEndedCallback(void(*callback)());
  std::vector<tetPiece> getNextBag(); //returns next 7 pieces in vector
private:
	void(*linesSentCallback)(int lines) = NULL;
	void(*linesReceivedCallback)(int lines) = NULL;
	void(*gameStartedCallback)() = NULL;
	void(*gameEndedCallback)() = NULL;
	bool startGameHandler(Tins::PDU &pdu);
	bool endGameHandler(Tins::PDU &pdu);
	bool lineHandler(Tins::PDU &pdu);
	Tins::Sniffer* lineSniffer;
	tetRandomPieceGen* rand;
  int seed;
  std::string interface;
};
}

#endif