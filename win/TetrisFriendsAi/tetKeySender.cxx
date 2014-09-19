#include "tetKeySender.hpp"
#include "tetConstants.hpp"
#include <Windows.h>
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
    INPUT ip;

    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Press the key
    ip.ki.wVk = keysym; // virtual-key code for the "a" key
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
    Sleep(tetConstants::keypress_duration_ms);
    // Release the key
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));
	}
};


tetKeySender::tetKeySender() : pimpl(new impl)
{
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
      pimpl->sendKey(tetConstants::rotate_right_key_win);
			break;
		case 2:
      pimpl->sendKey(tetConstants::rotate_right_key_win);
      Sleep(tetConstants::pause_between_keypresses_ms);
      pimpl->sendKey(tetConstants::rotate_right_key_win);
			break;
		case 3:
      pimpl->sendKey(tetConstants::rotate_left_key_win);
			break;
	}
  Sleep(tetConstants::switch_key_pause_ms);
  if (col < tetConstants::center_column_idx) {
    for (int i = tetConstants::center_column_idx; i > col; i--) {
      pimpl->sendKey(tetConstants::move_left_key_win);
      Sleep(tetConstants::pause_between_keypresses_ms);
    }
	} else if (col > tetConstants::center_column_idx) {
    for (int i = tetConstants::center_column_idx; i < col; i++) {
      pimpl->sendKey(tetConstants::move_right_key_win);
      Sleep(tetConstants::pause_between_keypresses_ms);
    }
	}
  Sleep(tetConstants::switch_key_pause_ms);
  pimpl->sendKey(tetConstants::drop_key_win);
  Sleep(tetConstants::pause_between_drops_ms);
}
void tetKeySender::swapHold() const
{
  pimpl->sendKey(tetConstants::hold_key_win);
}