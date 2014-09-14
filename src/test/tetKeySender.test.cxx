#include "tetKeySender.hpp"

using namespace Tetris;

void t1(tetKeySender ks)
{
	this_thread::sleep_for(chrono::milliseconds(5000));
	ks.dropPiece(0,4);
	ks.dropPiece(1,0);
	ks.dropPiece(2,9);
}

void t2(tetKeySender ks)
{
}

void t3(tetKeySender ks)
{
	this_thread::sleep_for(chrono::milliseconds(5000));
	ks.dropPiece(1,0);
	ks.dropPiece(2,4);
	ks.dropPiece(3,9);
}

int main ()
{
	tetKeySender ks;
	t3(ks);
}

//100: 1
//120: 1
//140: 1
//160: 1
//180: 1
//185: 1
//190: 2
//200: 2
//220: 2
//225: 3
//230: 3
//240: 3
//250: 3
//260: 3
//270: 3/4
//280: 3/4
//290: 3/4
//300: 4
//310: 4
//320: 4-6
//330: 4-6
//340: