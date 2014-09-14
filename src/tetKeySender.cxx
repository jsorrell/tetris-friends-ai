#include "tetKeySender.hpp"

using namespace Tetris;

tetKeySender::tetKeySender()
{
	display = XOpenDisplay(NULL);
}

void tetKeySender::sendKeyEvent(unsigned keysym, bool press)
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

void tetKeySender::sendKeyTime(unsigned keysym, int time)
{

	// Obtain the X11 display.
	Display *display = XOpenDisplay(0);
	if(display == NULL)
    return;

	XTestFakeKeyEvent(display, XKeysymToKeycode(display,keysym), True, CurrentTime);
	this_thread::sleep_for(chrono::milliseconds(time));
	XTestFakeKeyEvent(display, XKeysymToKeycode(display,keysym), False, time);

// Done.
   XCloseDisplay(display);
}

void tetKeySender::dropPiece(int rotation, int col)
{
	cout << "dropPiece rotated right " << rotation << " in column " << col << endl;
	switch(rotation) {
		case 0:
			break;
		case 1:
			sendKeyTime(tetConstants::rotate_right_key,tetConstants::key_hold_time_ms[1]);
			break;
		case 2:
			sendKeyTime(tetConstants::rotate_right_key,tetConstants::key_hold_time_ms[1]);
			this_thread::sleep_for(chrono::milliseconds(tetConstants::switch_key_pause_ms));
			sendKeyTime(tetConstants::rotate_right_key,tetConstants::key_hold_time_ms[1]);
			break;
		case 3:
			sendKeyTime(tetConstants::rotate_left_key,tetConstants::key_hold_time_ms[1]);
			break;
	}

	this_thread::sleep_for(chrono::milliseconds(tetConstants::switch_key_pause_ms));

	if (col < tetConstants::center_column_idx) {
		sendKeyTime(tetConstants::move_left_key,tetConstants::key_hold_time_ms[tetConstants::center_column_idx-col]);
	} else if (col > tetConstants::center_column_idx) {
		sendKeyTime(tetConstants::move_right_key,tetConstants::key_hold_time_ms[col-tetConstants::center_column_idx]);
	}
	this_thread::sleep_for(chrono::milliseconds(tetConstants::switch_key_pause_ms));
	sendKeyTime(tetConstants::drop_key,tetConstants::key_hold_time_ms[1]);
	this_thread::sleep_for(chrono::milliseconds(tetConstants::pause_between_drops_ms));
}
void tetKeySender::swapHold()
{
	sendKeyTime(tetConstants::hold_key,tetConstants::key_hold_time_ms[1]);
	this_thread::sleep_for(chrono::milliseconds(tetConstants::pause_between_drops_ms));
}