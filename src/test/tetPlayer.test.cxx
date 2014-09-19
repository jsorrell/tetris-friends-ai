#include "tetPlayer.hpp"
#include "tetConstants.hpp"

using namespace std;
using namespace Tetris;

int main(int argc, char *argv[])
{
	string interface = "{C25A865C-49E4-4656-8463-FC8155E5D95C}";
	if (argc >= 2)
		interface = argv[1];
	tetPlayer Player(interface);
	Player.go();
}