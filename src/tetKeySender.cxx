#include "tetKeySender.hpp"
#define XK_Down				0xff54
#define XK_Up 				0xff52
#define XK_Right 			0xff53
#define XK_Left 			0xff51
#define XK_KP_Space 	0xff80
#define XK_Shift_L    0xffe1
#define XK_Control_R  0xffe4

#define MOVE_LEFT_COMMAND "Left"
#define MOVE_RIGHT_COMMAND "Right"
#define ROTATE_LEFT_COMMAND "Control_R"
#define ROTATE_RIGHT_COMMAND "Up"
#define DROP_COMMAND "space"
#define HOLD_COMMAND "Shift_L"

#define MS_KEYPRESS_DURATION 50
#define MS_BETWEEN_COMMANDS 40

using namespace Tetris;

tetKeySender::tetKeySender()
{
	xdo = xdo_new(NULL);
}

void tetKeySender::sendKeySequence()
{
	vector<string> ks = keyseq;
	this->keyseq = {};
	for (vector<string>::iterator it = ks.begin(); it != ks.end(); ++it){
		xdo_send_keysequence_window_down(xdo, 0, (*it).c_str(), 0);
		this_thread::sleep_for(chrono::milliseconds(MS_KEYPRESS_DURATION));
		xdo_send_keysequence_window_up(xdo, 0, (*it).c_str(), 0);
		this_thread::sleep_for(chrono::milliseconds(MS_BETWEEN_COMMANDS));
	}
}

inline void tetKeySender::appendToKeySeq(const string key) {
	keyseq.push_back(key);
}

void tetKeySender::dropPiece(int rotation, int col)
{
	cout << "dropPiece rotated right " << rotation << " in column " << col << endl;
	string seq;
	switch(rotation) {
		case 0:
			break;
		case 1:
			appendToKeySeq(ROTATE_RIGHT_COMMAND);
			break;
		case 2:
			appendToKeySeq(ROTATE_RIGHT_COMMAND);
			appendToKeySeq(ROTATE_RIGHT_COMMAND);
			break;
		case 3:
			appendToKeySeq(ROTATE_LEFT_COMMAND);
			break;
	}

	if (col < centerColumn) {
		for (int i = centerColumn; i > col; i--)
			appendToKeySeq(MOVE_LEFT_COMMAND);
	} else if (col > centerColumn) {
		for (int i = centerColumn; i < col; i++)
			appendToKeySeq(MOVE_RIGHT_COMMAND);
	}
	appendToKeySeq(DROP_COMMAND);
	sendKeySequence();

}
void tetKeySender::swapHold()
{
	appendToKeySeq(HOLD_COMMAND);
	sendKeySequence();
}