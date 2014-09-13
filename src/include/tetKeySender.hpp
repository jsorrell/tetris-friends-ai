#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
extern "C" {
#include <xdo.h>
}

using namespace std;

namespace Tetris {

class tetKeySender {
public:
	tetKeySender();
	void dropPiece(int rotation, int col);
	void swapHold();
private:
	void sendKeySequence();
	void appendToKeySeq(const string key);
	xdo_t *xdo;
	static const int centerColumn = 4;
	vector <string> keyseq;
};
}