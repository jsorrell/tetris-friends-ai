#ifndef _TETCORE_H_
#define _TETCORE_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
//TODO:
#include <cassert>
#include <type_traits>
using namespace std;

namespace Tetris {

/* Pieces */
class tetPiece {
public:
	tetPiece(string typeName);
	vector<vector<bool>>getShape(int direction) const;
	vector<int>lowestInEachCol(int direction) const;
	string getTypeName() const;
	friend ostream& operator<<(ostream &out, const tetPiece&x){out << x.getTypeName(); return out;};
	inline bool operator==(const tetPiece& rhs){return this->type == rhs.type;}
	inline bool operator!=(const tetPiece& rhs){return !(this->type==rhs.type);}
	static const int xOffset = -1;
	static const int yOffset = -2;
private:
	enum minoType {ZPiece,LPiece,OPiece,SPiece,IPiece,JPiece,TPiece};
	minoType type;
};


/* End Pieces */

struct tetMove{
	tetPiece piece = tetPiece("Z");
	int direction;
	int x;
};

struct boardInfo {
	int numHoles;
	int aggHeight;//sum of heights of columns
	int bumpiness;//sum of abs of differences b/w adjacent columns
	int fullLines;
	bool toppedOut;
};


class tetBoard {
public:
	tetBoard(int width, int height);
	tetBoard(tetBoard *board);
	~tetBoard();
	int getWidth(){return _width;};
	int getHeight(){return _height;};

	bool isPieceAt(int x, int y);
	int colHeight(int col);
	void setPieceAt(int x, int y, bool val);
	int clearFullLines(); //returns number cleared
	void emptyBoard();

	//board heuristic information
	int numHoles();
	int aggHeight();
	int bumpiness();
	int fullLines();
	boardInfo getBoardInfo();
	void printBoard();
	bool toppedOut;

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
	int minX(tetPiece piece, int direction) const;
	int maxX(tetPiece piece, int direction) const;

	//board modification
	int dropPiece(tetPiece piece, int direction, int x);
	int dropPiece(tetMove move);
	tetPiece getHoldPiece() const;
	void setHoldPiece(tetPiece piece);
	boardInfo getBoardInfo() const; //returns heuristic info
	bool inBounds(tetPiece piece, int direction, int x) const;
	int findHitRow(tetPiece piece, int direction, int x) const;

	boardInfo testDrop(tetPiece piece, int direction, int x) const; //gets BoardInfo for test move
	tetBoard* board;
	bool getHoldFilled() const;

private:
	tetPiece holdPiece = tetPiece("Z");
	bool holdFilled = false;
};
}

#endif