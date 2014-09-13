#ifndef __TET_GAME_INFO__
#define __TET_GAME_INFO__

#include <cstdlib>
#include <string>
#include <tins/tins.h>
#include <regex>
#include <vector>
#include <thread>
#include "tetCore.hpp"

/* Collapse namespaces */
using namespace std;
using namespace Tins;

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
  vector<tetPiece> getNextBag(); //returns next 7 pieces in vector
private:
	void(*linesSentCallback)(int lines) = NULL;
	void(*linesReceivedCallback)(int lines) = NULL;
	void(*gameStartedCallback)() = NULL;
	void(*gameEndedCallback)() = NULL;
	bool startGameHandler(PDU &pdu);
	bool endGameHandler(PDU &pdu);
	bool lineHandler(PDU &pdu);
	Sniffer* lineSniffer;
	tetRandomPieceGen* rand;
  const string pieceMap[7] = {"Z","L","O","S","I","J","T"};
  const int msDelayFromStart = 2000;
  int seed;
};
}

#endif