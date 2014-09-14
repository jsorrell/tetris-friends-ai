#include "tetPlayer.hpp"

int main(int argc, char *argv[])
{
	string interface = tetConstants::default_interface;
	if (argc >= 2)
		interface = argv[1];
	tetPlayer Player(interface);
	Player.go();
}