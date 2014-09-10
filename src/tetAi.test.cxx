#include "tetAi.hpp"
#include "tetCore.hpp"
#include <random>
#include <thread>
using namespace TetCore;
using namespace TetAi;

int main()
{
	tetGame game(10,20);
	game.board->printBoard();
	tetAi ai;
	srand (time(NULL));
	int pieces = 0;
	int linesCleared = 0;
	for(int i = 0; i < 1000; i++) {
		cout<<"going for "<<++pieces<<endl;
		cout<<"Lines Cleared: "<<linesCleared<<endl;
		pieceType piece = static_cast<pieceType>(rand() % 7);
		tetMove move = ai.chooseMove(&game,piece);
		linesCleared+=game.dropPiece(move);
		game.board->printBoard();
		//cin.get();
	}
}