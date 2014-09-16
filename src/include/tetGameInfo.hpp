#ifndef __TET_GAME_INFO_H__
#define __TET_GAME_INFO_H__
#include <vector>
#include <string>
#include <memory>
#include "tetCore.hpp"

namespace Tetris {

class tetGameInfo {
public:
	tetGameInfo(std::string adaptor);
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
	struct impl; std::unique_ptr<impl> pimpl;
};
}

#endif