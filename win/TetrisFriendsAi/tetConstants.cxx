#include "tetConstants.hpp"

using namespace Tetris;

//Defaults
const std::string tetConstants::default_interface = "wlan0";
//Key Commands
const unsigned tetConstants::move_left_key = 0xFF51;
const unsigned tetConstants::move_right_key = 0xFF53;
const unsigned tetConstants::rotate_left_key = 0x7A;
const unsigned tetConstants::rotate_right_key = 0x78;
const unsigned tetConstants::drop_key = 0x20;
const unsigned tetConstants::hold_key = 0x63;
//windows keycodes
const unsigned tetConstants::move_left_key_win = 0x25;
const unsigned tetConstants::move_right_key_win = 0x27;
const unsigned tetConstants::rotate_left_key_win = 0x5A;
const unsigned tetConstants::rotate_right_key_win = 0x58;
const unsigned tetConstants::drop_key_win = 0x20;
const unsigned tetConstants::hold_key_win = 0x43;
//Timings
const int tetConstants::keypress_duration_ms = 60;
// const int tetConstants::pause_between_keypresses_ms = 80;
const int tetConstants::wait_to_play_first_piece_ms = 3300;
//const int tetConstants::key_hold_time_ms[6] = {0,100,190,240,310,500};
const int tetConstants::pause_between_keypresses_ms = 60;
const int tetConstants::switch_key_pause_ms = 60;
const int tetConstants::pause_between_drops_ms = 60;
const int tetConstants::pause_after_clear_ms = 300;
//tetPieces Declaration
const int tetConstants::x_offset = -1;
const int tetConstants::y_offset = -2;
//tetrisFriends: don't change these
const int tetConstants::center_column_idx = 4;
const std::string tetConstants::piecegen_map[7] = {"Z","L","O","S","I","J","T"};
const std::string tetConstants::listen_filter = "tcp and port 9339";
const std::string tetConstants::start_game_regex = "<var n='seed' t='n'>(\\d+)</var>";
const std::string tetConstants::end_game_regex = "%xt%TetrisLive%results%";
const std::string tetConstants::line_sent_regex = "%xt%TetrisLive%lineAttack%\\d+%\\d+%(\\d+)%";
const std::string tetConstants::line_received_regex = "%xt%lineAttack%\\d+%(\\d+)%";
