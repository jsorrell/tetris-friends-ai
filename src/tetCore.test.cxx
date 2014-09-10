#include "tetCore.hpp"
using namespace TetCore;

int main()
{
	tetGame game(10,20);
	// game.dropPiece(pieceType::IPiece,1,4);
	// game.dropPiece(pieceType::IPiece,1,4);
	// game.dropPiece(pieceType::OPiece,0,7);
	// game.board->printBoard();
	// game.dropPiece(pieceType::JPiece,3,5);
	// game.board->printBoard();
	while(true) {
		cout << "Enter piece name: ";
		string pieceName;
		cin >> pieceName;
		tetPiece piece(pieceName);
		cout << "Enter number of clockwise rotations[0-3]: ";
		int rotation;
		cin >> rotation;
		cout << "Enter x position to drop:[" << game.minX(piece.getType(),rotation) << "," << game.maxX(piece.getType(),rotation) << "]: ";
		int x;
		cin >> x;
		int linesCleared = game.dropPiece(piece.getType(),rotation,x);
		game.board->printBoard();
		cout << linesCleared << " lines cleared." << endl;
	}

	game.dropPiece(pieceType::ZPiece,0,3);
	game.board->printBoard();
	game.dropPiece(pieceType::LPiece,0,3);
	game.board->printBoard();
	game.dropPiece(pieceType::LPiece,0,4);
	game.dropPiece(pieceType::LPiece,3,8);
	game.board->printBoard();
	game.dropPiece(pieceType::IPiece,0,0);
	game.board->printBoard();

	return 0;
}