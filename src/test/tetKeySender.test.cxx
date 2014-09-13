#include "tetKeySender.hpp"

using namespace Tetris;

int main ()
{
	tetKeySender ks;
	this_thread::sleep_for(chrono::milliseconds(5000));
	ks.dropPiece(0,4);
	ks.dropPiece(1,0);
	ks.dropPiece(2,9);
}