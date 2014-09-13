#include "tetGameInfo.hpp"

using namespace std;
using namespace Tetris;

void lSend(int num)
{
	cout << "Send " << num << " Lines!" << endl;
}
void lReceived(int num)
{
	cout << "Received " << num << " Lines!" << endl;
}

int main()
{
	tetGameInfo gameInfo("wlan0");
	gameInfo.registerLinesSentCallback(lSend);
	gameInfo.registerLinesReceivedCallback(lReceived);
	gameInfo.captureLinesAsync();
	while(true){
		gameInfo.captureStart();
		cout << "Game Started!" << endl;
		vector<tetPiece> bag = gameInfo.getNextBag();
		for( std::vector<tetPiece>::const_iterator i = bag.begin(); i != bag.end(); ++i)
    	std::cout << *i << ' ';
  	cout<<endl;
		gameInfo.captureEnd();
		cout << "Game Ended!\n";
	}
	cout<<"done\n";
	return 0;
}