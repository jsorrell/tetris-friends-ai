#include "tetCore.hpp"

using namespace std;
using namespace Tetris;
/**************/
/***tetPiece***/
/**************/

tetPiece::tetPiece(string typeName)
{
	assert(typeName != "");

	switch (typeName[0]) {
		case 'z':
		case 'Z': type = minoType::ZPiece; return;
		case 'l':
		case 'L': type = minoType::LPiece; return;
		case 'o':
		case 'O': type = minoType::OPiece; return;
		case 's':
		case 'S': type = minoType::SPiece; return;
		case 'i':
		case 'I': type = minoType::IPiece; return;
		case 'j':
		case 'J': type = minoType::JPiece; return;
		case 't':
		case 'T': type = minoType::TPiece; return;
	}
	cerr << "invalid piecename parsed\n";
	exit(1);
}

vector<vector<bool>>tetPiece::getShape(int direction) const
{
	switch(type) {
	case minoType::ZPiece:
		switch (direction) {
			case 0:
			case 2: return {{false,false,false,false},{false,true,true,false},{true,true,false,false},{false,false,false,false}};
			case 1: return {{false,true,false,false},{false,true,true,false},{false,false,true,false},{false,false,false,false}};
			case 3: return {{true,false,false,false},{true,true,false,false},{false,true,false,false},{false,false,false,false}};
		}
	case minoType::LPiece:
		switch (direction) {
			case 0: return {{false,false,false,false},{true,true,true,false},{false,false,true,false},{false,false,false,false}};
			case 1: return {{false,true,true,false},{false,true,false,false},{false,true,false,false},{false,false,false,false}};
			case 2: return {{true,false,false,false},{true,true,true,false},{false,false,false,false},{false,false,false,false}};
			case 3: return {{false,true,false,false},{false,true,false,false},{true,true,false,false},{false,false,false,false}};
		}
	case minoType::OPiece:
		switch (direction) {
			case 0:
			case 1:
			case 2:
			case 3: return {{false,false,false,false},{false,true,true,false},{false,true,true,false},{false,false,false,false}};
		}
	case minoType::SPiece:
		switch (direction) {
			case 0:
			case 2: return {{false,false,false,false},{true,true,false,false},{false,true,true,false},{false,false,false,false}};
			case 1: return {{false,false,true,false},{false,true,true,false},{false,true,false,false},{false,false,false,false}};
			case 3: return {{false,true,false,false},{true,true,false,false},{true,false,false,false},{false,false,false,false}};
		}
	case minoType::IPiece:
		switch (direction) {
			case 0:
			case 2: return {{false,false,false,false},{true,true,true,true},{false,false,false,false},{false,false,false,false}};
			case 1: return {{false,false,true,false},{false,false,true,false},{false,false,true,false},{false,false,true,false}};
			case 3: return {{false,true,false,false},{false,true,false,false},{false,true,false,false},{false,true,false,false}};
		}
	case minoType::JPiece:
		switch (direction) {
			case 0: return {{false,false,false,false},{true,true,true,false},{true,false,false,false},{false,false,false,false}};
			case 1: return {{false,true,false,false},{false,true,false,false},{false,true,true,false},{false,false,false,false}};
			case 2: return {{false,false,true,false},{true,true,true,false},{false,false,false,false},{false,false,false,false}};
			case 3: return {{true,true,false,false},{false,true,false,false},{false,true,false,false},{false,false,false,false}};
		}
	case minoType::TPiece:
		switch(direction) {
			case 0: return {{false,false,false,false},{true,true,true,false},{false,true,false,false},{false,false,false,false}};
			case 1: return {{false,true,false,false},{false,true,true,false},{false,true,false,false},{false,false,false,false}};
			case 2: return {{false,true,false,false},{true,true,true,false},{false,false,false,false},{false,false,false,false}};
			case 3: return {{false,true,false,false},{true,true,false,false},{false,true,false,false},{false,false,false,false}};
		}
	}
	return {};
}

vector<int>tetPiece::lowestInEachCol(int direction) const
{
	switch (type) {
		case minoType::ZPiece:
			switch (direction) {
				case 0:
				case 2: return {2,1,1,4};
				case 1: return {4,0,1,4};
				case 3: return {0,1,4,4};
			}
		case minoType::LPiece:
			switch (direction) {
				case 0: return {1,1,1,4};
				case 1: return {4,0,0,4};
				case 2: return {0,1,1,4};
				case 3: return {2,0,4,4};
			}
		case minoType::OPiece:
			switch (direction) {
				case 0:
				case 1:
				case 2:
				case 3: return {4,1,1,4};
			}
		case minoType::SPiece:
			switch (direction) {
				case 0:
				case 2: return {1,1,2,4};
				case 1: return {4,1,0,4};
				case 3: return {1,0,4,4};
			}
		case minoType::IPiece:
			switch (direction) {
				case 0:
				case 2: return {1,1,1,1};
				case 1: return {4,4,0,4};
				case 3: return {4,0,4,4};
			}
		case minoType::JPiece:
			switch (direction) {
				case 0: return {1,1,1,4};
				case 1: return {4,0,2,4};
				case 2: return {1,1,0,4};
				case 3: return {0,0,4,4};
			}
		case minoType::TPiece:
			switch (direction) {
				case 0: return {1,1,1,4};
				case 1: return {4,0,1,4};
				case 2: return {1,0,1,4};
				case 3: return {1,0,4,4};
			}
	}
	return {};
}

string tetPiece::getTypeName() const
{
	switch(type) {
		case minoType::ZPiece:
			return "Z";
		case minoType::LPiece:
			return "L";
		case minoType::OPiece:
			return "O";
		case minoType::SPiece:
			return "S";
		case minoType::IPiece:
			return "I";
		case minoType::JPiece:
			return "J";
		case minoType::TPiece:
			return "T";
	}
	return "[Invalid Piece]";
}


/**************/
/***tetBoard***/
/**************/

tetBoard::tetBoard(int width, int height)
{
	_width = width;
	_height = height;
	toppedOut = false;

	board.resize(width*height,false);
}

tetBoard::~tetBoard()
{
}

tetBoard::tetBoard(tetBoard *cpyBoard)
{
	_width = cpyBoard->getWidth();
	_height = cpyBoard->getHeight();
	toppedOut = cpyBoard->toppedOut;
	board = cpyBoard->board;
}

int tetBoard::getBoardIdx(int x, int y)
{
	return x*getHeight()+y;
}

bool tetBoard::isPieceAt(int x, int y)
{
	return board[getBoardIdx(x,y)];
}

vector<bool> tetBoard::getRow(int y)
{
	vector<bool> row;
	for (int x = 0; x < getWidth(); x++)
	{
		row.push_back(isPieceAt(x,y));
	}
	return row;
}
vector<bool> tetBoard::getCol(int x)
{
	vector<bool> col;
	for (int y = 0; y < getHeight(); y++)
	{
		col.push_back(isPieceAt(x,y));
	}
	return col;
}

int tetBoard::colHeight(int x)
{
	vector<bool> col = getCol(x);
	bool t[1] = {true};
	int topIdx = find_end(col.begin(),col.end(),t,t+1)-col.begin();
	if (topIdx == getHeight())
		return 0;
	else
		return topIdx+1;
}

void tetBoard::setPieceAt(int x, int y, bool val)
{
	if (y >= getHeight())
		toppedOut = true;
	board[getBoardIdx(x,y)] = val;
}

void tetBoard::emptyBoard()
{
	toppedOut = false;
	for (int x = 0; x < getWidth(); x++)
		for (int y = 0; y < getHeight(); y++)
			setPieceAt(x,y,false);
}

int tetBoard::numHoles()
{
	int holes = 0;
	for (int x = 0; x < getWidth(); x++) {
		vector<bool> col = getCol(x);
		holes += count(col.begin(),col.begin()+colHeight(x),false);
	}
	return holes;
}

int tetBoard::aggHeight()
{
	int aggHeight = 0;
	for (int x = 0; x < getWidth(); x++) {
		aggHeight += colHeight(x);
	}
	return aggHeight;
}

int tetBoard::bumpiness()
{
	int bumpiness = 0;
	int lastHeight = colHeight(0);
	int nextHeight;
	for (int x = 1; x < getWidth(); x++) {
		nextHeight = colHeight(x);
		bumpiness += abs(nextHeight-lastHeight);
		lastHeight = nextHeight;
	}
	return bumpiness;
}

int tetBoard::fullLines()
{
	int numFullRows = 0;
	for (int y = 0; y < getHeight(); y++)
	{
		vector<bool> row = getRow(y);
		vector<bool> fullRow(getWidth(),true);
		if (row == fullRow)
			numFullRows++;
	}
	return numFullRows;
}

void tetBoard::removeRow(int y)
{
	for (int x = 0; x < getWidth(); x++)
	{
		int idx = getBoardIdx(x,y);
		board.erase(board.begin()+idx);
		int idx2 = getBoardIdx(x,getHeight()-1);
		board.insert(board.begin()+idx2,false);
	}
}

int tetBoard::clearFullLines()
{
	int numFullLines = 0;
	for (int y = 0; y < getHeight(); y++)
	{
		vector<bool> row = getRow(y);
		vector<bool> fullRow(getWidth(),true);
		if (row == fullRow) {
			numFullLines++;
			removeRow(y);
		}
	}
	return numFullLines;
}

//board heuristic information
boardInfo tetBoard::getBoardInfo()
{
	boardInfo info;
	info.aggHeight = aggHeight();
	info.numHoles = numHoles();
	info.fullLines = fullLines();
	info.bumpiness = bumpiness();
	info.toppedOut = toppedOut;
	return info;
}

void tetBoard::printBoard()
{
	for (int row = getHeight()-1; row >=0; row--) {
		for (int col = 0; col < getWidth(); col++)
			if (isPieceAt(col,row))
				cout<<"\u25A0 ";
			else
				cout<<"\u25A1 ";
			cout<<endl;
	}
	cout<<endl;
	cout<<"numHoles: " << numHoles() << endl;
	cout<<"aggHeight: " << aggHeight() << endl;
	cout<<"fullLines: " << fullLines() << endl;
	cout<<"bumpiness: " << bumpiness() << endl;
	cout<<endl;
}

/*************/
/***tetGame***/
/*************/

tetPiece tetGame::getHoldPiece() const
{
	if (!holdFilled) {
		cout << "got bad hold piece\n";
		exit(1);
	}
	return holdPiece;
}

bool tetGame::getHoldFilled() const
{
	return holdFilled;
}

void tetGame::setHoldPiece(tetPiece piece)
{
	holdFilled = true;
	holdPiece = piece;
}

tetGame::tetGame(int width, int height)
{
	board = new tetBoard(width,height);
	holdFilled = false;
}
void tetGame::reset()
{
	board->emptyBoard();
	holdFilled = false;
}

int tetGame::minX(tetPiece piece, int direction) const
{
	vector<int> lowestInEachCol = piece.lowestInEachCol(direction);
	if (lowestInEachCol[1] == 4 && lowestInEachCol[0] == 4)
		return -1;
	if (lowestInEachCol[0] == 4)
		return 0;
	return 1;
}

int tetGame::maxX(tetPiece piece, int direction) const
{
	vector<int> lowestInEachCol = piece.lowestInEachCol(direction);
	if (lowestInEachCol[2] == 4 && lowestInEachCol[3] == 4)
		return board->getWidth()-1;
	if (lowestInEachCol[3] == 4)
		return board->getWidth()-2;
	return board->getWidth()-3;

}

bool tetGame::inBounds(tetPiece piece, int direction, int x) const
{
	return x <= maxX(piece,direction) && x >= minX(piece,direction);
}

int tetGame::findHitRow(tetPiece piece, int direction, int x) const
{
	//leaving as an assertion for now
	assert(inBounds(piece,direction,x));

	vector<int> lowestInEachCol = piece.lowestInEachCol(direction);
	int hitRow = 0;
	for (int relCol = 0; relCol < 4; relCol++) {
		int col = relCol+x+tetPiece::xOffset;
		if (0<=col && col<board->getWidth()) {
			int colHeight = board->colHeight(col);
			if (lowestInEachCol[relCol] < 4) {
				int colHitRow = colHeight - lowestInEachCol[relCol]-tetPiece::yOffset;
				hitRow = max(colHitRow,hitRow);
			}
		}
	}
	return hitRow;
}

//board modification
int tetGame::dropPiece(tetPiece piece, int direction, int x)
{
	int hitRow = findHitRow(piece,direction,x);
	vector<vector<bool>> shape = piece.getShape(direction);
	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			if (shape[row][col])
				board->setPieceAt(x+col+tetPiece::xOffset,hitRow+row+tetPiece::yOffset,true);
	return board->clearFullLines();
}

int tetGame::dropPiece(tetMove move)
{
	return dropPiece(move.piece, move.direction, move.x);
}

boardInfo tetGame::getBoardInfo() const
{
	return board->getBoardInfo();
}
boardInfo tetGame::testDrop(tetPiece piece, int direction, int x) const
{
	tetBoard testBoard(board);
	//FIXME: copied code
	int hitRow = findHitRow(piece,direction,x);
	vector<vector<bool>> shape = piece.getShape(direction);
	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			if (shape[row][col])
				testBoard.setPieceAt(x+col+tetPiece::xOffset,hitRow+row+tetPiece::yOffset,true);
	return testBoard.getBoardInfo();
}