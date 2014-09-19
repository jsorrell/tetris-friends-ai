#include "tetCore.hpp"
using namespace std;
using namespace Tetris;

int main()
{
	tetGame game(10,20);
	while(true) {
		cout << "Enter piece name: ";
		string pieceName;
		cin >> pieceName;
		tetPiece piece(pieceName);
		cout << "Enter number of clockwise rotations[0-3]: ";
		int rotation;
		cin >> rotation;
		cout << "Enter x position to drop:[" << game.minX(piece,rotation) << "," << game.maxX(piece,rotation) << "]: ";
		int x;
		cin >> x;
		int linesCleared = game.dropPiece(piece,rotation,x);
		game.board->printBoard();
		cout << linesCleared << " lines cleared." << endl;
	}
	return 0;
}