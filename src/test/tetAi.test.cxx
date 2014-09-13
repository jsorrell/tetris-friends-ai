#include "tetAi.hpp"
#include "tetCore.hpp"
#include <random>
#include <unistd.h>
#include <chrono>
#include <thread>
using namespace Tetris;

int main()
{
	tetGame game(10,20);
	game.board->printBoard();
	tetAi ai;
	srand (time(NULL));
	int linesCleared = 0;
	int linesSent = 0;
	vector<string> pieces = {"Z","L","O","S","I","J","T"};
	int randomIndex = rand() % pieces.size();
	game.setHoldPiece(tetPiece(pieces[randomIndex]));
	while(true) {
		random_shuffle(pieces.begin(), pieces.end());
		for (vector<string>::iterator it=pieces.begin(); it!=pieces.end(); ++it){
			cout<<"Lines Cleared: "<<linesCleared<<endl;
			cout<<"Lines Sent: "<<linesSent<<endl;
			tetPiece piece(*it);
			tetMove move;
			bool usingHold = ai.chooseMove(game,piece,&move);
			if (usingHold){
				cout << "Using " << game.getHoldPiece() << " piece" << endl;
				cout << "Replacing Hold With " << piece << endl;
				game.setHoldPiece(piece);
			} else {
				cout << "Using " << piece << " piece" << endl;
			}
			int curLinesCleared = game.dropPiece(move);
			linesCleared+=curLinesCleared;
			switch(curLinesCleared) {
				case 0:
				case 1:
					break;
				case 2:
					linesSent++;
					break;
				case 3:
					linesSent+=2;
					break;
				case 4:
					linesSent+=4;
					break;
			}

			if (game.board->toppedOut) {
				cout << "Topped Out" << endl;
				exit(0);
			}
			game.board->printBoard();
			this_thread::sleep_for(chrono::milliseconds(200));
		}
		//cin.get();

	}
}