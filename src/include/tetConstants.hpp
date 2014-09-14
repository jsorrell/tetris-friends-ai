#ifndef __TET_CONSTANTS__
#define __TET_CONSTANTS__
#include <string>
namespace Tetris{

struct tetConstants {
	//Defaults
	static const std::string default_interface;
	//Key Commands
	static const unsigned move_left_key;
	static const unsigned move_right_key;
 	static const unsigned rotate_left_key;
	static const unsigned rotate_right_key;
	static const unsigned drop_key;
	static const unsigned hold_key;
	//Timings
	static const int keypress_duration_ms;
	// static const int pause_between_keypresses_ms;
	static const int pause_between_drops_ms;
  static const int wait_to_play_first_piece_ms;
  static const int key_hold_time_ms[6];
  static const int switch_key_pause_ms;
	//tetPieces Declaration
	static const int x_offset;
	static const int y_offset;
	//tetrisFriends: don't change these
	static const int center_column_idx;
	static const std::string piecegen_map[7];
	static const std::string listen_filter;
	static const std::string start_game_regex;
	static const std::string end_game_regex;
	static const std::string line_sent_regex;
	static const std::string line_received_regex;
	//AIConstants::::::::TODO
};
}
#endif