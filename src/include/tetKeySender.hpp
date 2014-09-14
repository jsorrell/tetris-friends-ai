#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <ctime>
#include <vector>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include "tetConstants.hpp"

using namespace std;

namespace Tetris {

class tetKeySender {
public:
	tetKeySender();
	void dropPiece(int rotation, int col);
	void swapHold();
private:
	void sendKeyTime(unsigned keysym, int time);
	void sendKeyEvent(unsigned keysym, bool press);
	Display *display;
};
}