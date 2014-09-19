#include "tetKeySender.hpp"
#include <X11/Xlib.h>
// #include <X11/extensions/XTest.h>
#include "tetConstants.hpp"
#include <thread>
#include <chrono>
//temp
#include <iostream>


using namespace std;
using namespace Tetris;

struct tetKeySender::impl
{
	void sendKey(unsigned keysym)
	{
		sendKeyEvent(keysym,true);
		this_thread::sleep_for(chrono::milliseconds(tetConstants::keypress_duration_ms));
		sendKeyEvent(keysym,false);
	}
	void sendKeyEvent(unsigned keysym, bool press)
	{
		Display *display = XOpenDisplay(0);
		if(display == NULL)
	    return;
		XKeyEvent event = {0};
		if (press)
			event.type = KeyPress;
		else
			event.type = KeyRelease;
		event.display = display;
		event.root = XDefaultRootWindow(display);
		event.keycode = XKeysymToKeycode(display,keysym);
		event.same_screen = True;
		event.time = CurrentTime;
	 	int revert;
	 	XGetInputFocus(display, &event.window, &revert);
	 	XSendEvent(display,event.window, True, KeyPressMask, (XEvent *)&event);
	 	XCloseDisplay(display);
	}
	Display *display;
};


tetKeySender::tetKeySender() : pimpl(new impl)
{
	pimpl->display = XOpenDisplay(NULL);
}

tetKeySender::~tetKeySender()
{
}

void tetKeySender::dropPiece(int rotation, int col) const
{
	cout << "dropPiece rotated right " << rotation << " in column " << col << endl;
	switch(rotation) {
		case 0:
			break;
		case 1:
			pimpl->sendKey(tetConstants::rotate_right_key);
			break;
		case 2:
			pimpl->sendKey(tetConstants::rotate_right_key);
			this_thread::sleep_for(chrono::milliseconds(tetConstants::pause_between_keypresses_ms));
			pimpl->sendKey(tetConstants::rotate_right_key);
			break;
		case 3:
			pimpl->sendKey(tetConstants::rotate_left_key);
			break;
	}
	this_thread::sleep_for(chrono::milliseconds(tetConstants::switch_key_pause_ms));

	if (col < tetConstants::center_column_idx) {
		for (int i = tetConstants::center_column_idx; i > col; i-- ){
			pimpl->sendKey(tetConstants::move_left_key);
			this_thread::sleep_for(chrono::milliseconds(tetConstants::pause_between_keypresses_ms));
		}
	} else if (col > tetConstants::center_column_idx) {
		for (int i = tetConstants::center_column_idx; i < col; i++ ) {
			pimpl->sendKey(tetConstants::move_right_key);
			this_thread::sleep_for(chrono::milliseconds(tetConstants::pause_between_keypresses_ms));
		}
	}
	this_thread::sleep_for(chrono::milliseconds(tetConstants::switch_key_pause_ms));
	pimpl->sendKey(tetConstants::drop_key);
	this_thread::sleep_for(chrono::milliseconds(tetConstants::pause_between_drops_ms));
}
void tetKeySender::swapHold() const
{
	pimpl->sendKey(tetConstants::hold_key);
}