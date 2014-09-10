#ifndef _TETCORE_H_
#define _TETCORE_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
//TODO:
#include <cassert>

using namespace std;

namespace TetCore{

enum class pieceType {ZPiece,LPiece,OPiece,SPiece,IPiece,JPiece,TPiece};

//TODO: convert to this
struct tetMove{
	pieceType type;
	int direction;
	int x;
};

class tetPiece {
public:
	tetPiece(pieceType type);
	tetPiece(string typeName);
	vector< vector<bool> > getShape(int direction);
	vector<int>lowestInEachCol(int direction);
	static string getTypeName(pieceType type);
	static pieceType parseType(string typeName);
	pieceType getType();
private:
	pieceType _type;
};

struct boardInfo {
	int numHoles;
	int aggHeight;//sum of heights of columns
	int bumpiness;//sum of abs of differences b/w adjacent columns
	int fullLines;
};


class tetBoard {
public:
	tetBoard(int width, int height);
	tetBoard(tetBoard *board);
	~tetBoard();
	int getWidth(){return _width;};
	int getHeight(){return _height;};

	bool isPieceAt(int x, int y);
	int colHeight(int x);
	void setPieceAt(int x, int y, bool val);
	int clearFullLines();//returns number cleared
	void emptyBoard();

	//board heuristic information
	int numHoles();
	int aggHeight();
	int bumpiness();
	int fullLines();
	boardInfo getBoardInfo();
	void printBoard();

private:
	int _width;
	int _height;
	vector<bool> board; //idx = row*width+col
	int getBoardIdx(int x,int y);
	vector<bool> getRow(int y);
	vector<bool> getCol(int x);
	void removeRow(int y);
};

class tetGame {
public:
	tetGame(int width, int height);
	void reset();
	int minX(pieceType type, int direction);
	int maxX(pieceType type, int direction);

	//board modification
	int dropPiece(pieceType type, int direction, int x);
	int dropPiece(tetMove move);
	boardInfo getBoardInfo(); //returns heuristic info
	bool inBounds(pieceType type, int direction, int x);
	int findHitRow(pieceType type, int direction, int x);

	boardInfo testDrop(pieceType type, int direction, int x); //gets BoardInfo for test move
	tetBoard* board;

private:
	tetPiece hold = pieceType::IPiece; //needs to be initialized
	bool holdFilled = false;
};
}

#endif