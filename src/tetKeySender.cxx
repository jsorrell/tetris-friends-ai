#include "tetKeySender.hpp"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include "tetConstants.hpp"
#include <thread>
#include <chrono>
//temp
#include <iostream>


using namespace std;
using namespace Tetris;


struct tetKeySender::impl
{
	void sendKeyTime(unsigned keysym, int inTime, int forTime)
	{
		// Obtain the X11 display.
		Display *display = XOpenDisplay(0);
		if(display == NULL)
	    return;

		XTestFakeKeyEvent(display, XKeysymToKeycode(display,keysym), True, inTime);
		XTestFakeKeyEvent(display, XKeysymToKeycode(display,keysym), False, forTime);

		// Done.
		XCloseDisplay(display);
	}
	void sendKeyEvent(unsigned keysym, bool press)
	{
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
	 	cout << "sending " << event.type << endl;
	 	XSendEvent(display,event.window, True, KeyPressMask, (XEvent *)&event);
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
			pimpl->sendKeyTime(tetConstants::rotate_right_key,tetConstants::pause_between_drops_ms,tetConstants::key_hold_time_ms[1]);
			break;
		case 2:
			pimpl->sendKeyTime(tetConstants::rotate_right_key,tetConstants::pause_between_drops_ms,tetConstants::key_hold_time_ms[1]);
			pimpl->sendKeyTime(tetConstants::rotate_right_key,tetConstants::switch_key_pause_ms,tetConstants::key_hold_time_ms[1]);
			break;
		case 3:
			pimpl->sendKeyTime(tetConstants::rotate_left_key,tetConstants::pause_between_drops_ms,tetConstants::key_hold_time_ms[1]);
			break;
	}

	if (col < tetConstants::center_column_idx) {
		for (int i = tetConstants::center_column_idx; i > col; i-- )
		pimpl->sendKeyTime(tetConstants::move_left_key,tetConstants::switch_key_pause_ms,tetConstants::key_hold_time_ms[1]);
	} else if (col > tetConstants::center_column_idx) {
		for (int i = tetConstants::center_column_idx; i < col; i++ )
			pimpl->sendKeyTime(tetConstants::move_right_key,tetConstants::switch_key_pause_ms,tetConstants::key_hold_time_ms[1]);
	}
	pimpl->sendKeyTime(tetConstants::drop_key,tetConstants::switch_key_pause_ms,tetConstants::key_hold_time_ms[1]);
}
void tetKeySender::swapHold() const
{
	pimpl->sendKeyTime(tetConstants::hold_key,tetConstants::pause_between_drops_ms,tetConstants::key_hold_time_ms[1]);
}