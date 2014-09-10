#include "tetCore.hpp"

using namespace std;
using namespace TetCore;

/**************/
/***tetPiece***/
/**************/
tetPiece::tetPiece(pieceType type)
{
	_type = type;
}
tetPiece::tetPiece(string typeName)
{
	_type = parseType(typeName);
}
vector< vector<bool> > tetPiece::getShape(int direction)
{
	vector< vector<bool> > shape;
	switch(_type) {
		case pieceType::SPiece:
			switch (direction) {
				case 0:
				case 2: shape = {{false,false,false,false},{false,true,true,false},{false,false,true,true},{false,false,false,false}}; break;
				case 1:
				case 3: shape = {{false,false,false,false},{false,false,false,true},{false,false,true,true},{false,false,true,false}}; break;
			}
			break;
		case pieceType::JPiece:
			switch (direction) {
				case 0: shape = {{false,false,false,false},{false,false,false,false},{false,true,true,true},{false,true,false,false}}; break;
				case 1: shape = {{false,false,false,false},{false,true,true,false},{false,false,true,false},{false,false,true,false}}; break;
				case 2: shape = {{false,false,false,false},{false,false,false,true},{false,true,true,true},{false,false,false,false}}; break;
				case 3: shape = {{false,false,false,false},{false,false,true,false},{false,false,true,false},{false,false,true,true}}; break;
			}
			break;
		case pieceType::OPiece:
			switch (direction) {
				case 0:
				case 1:
				case 2:
				case 3: shape = {{false,false,false,false},{false,true,true,false},{false,true,true,false},{false,false,false,false}}; break;
			}
			break;
		case pieceType::ZPiece:
			switch (direction) {
				case 0:
				case 2: shape = {{false,false,false,false},{false,false,true,true},{false,true,true,false},{false,false,false,false}}; break;
				case 1:
				case 3: shape = {{false,false,false,false},{false,false,true,false},{false,false,true,true},{false,false,false,true}}; break;
			}
			break;
		case pieceType::IPiece:
			switch (direction) {
				case 0:
				case 2: shape = {{false,false,false,false},{false,false,false,false},{true,true,true,true},{false,false,false,false}}; break;
				case 1:
				case 3: shape = {{false,false,true,false},{false,false,true,false},{false,false,true,false},{false,false,true,false}}; break;
			}
			break;
		case pieceType::LPiece:
			switch (direction) {
				case 0: shape = {{false,false,false,false},{false,false,false,false},{false,true,true,true},{false,false,false,true}}; break;
				case 1: shape = {{false,false,false,false},{false,false,true,false},{false,false,true,false},{false,true,true,false}}; break;
				case 2: shape = {{false,false,false,false},{false,true,false,false},{false,true,true,true},{false,false,false,false}}; break;
				case 3: shape = {{false,false,false,false},{false,false,true,true},{false,false,true,false},{false,false,true,false}}; break;
			}
			break;
		case pieceType::TPiece:
			switch (direction) {
				case 0: shape = {{false,false,false,false},{false,false,false,false},{false,true,true,true},{false,false,true,false}}; break;
				case 1: shape = {{false,false,false,false},{false,false,true,false},{false,true,true,false},{false,false,true,false}}; break;
				case 2: shape = {{false,false,false,false},{false,false,true,false},{false,true,true,true},{false,false,false,false}}; break;
				case 3: shape = {{false,false,false,false},{false,false,true,false},{false,false,true,true},{false,false,true,false}}; break;
			}
			break;

	}
	return shape;
}

vector<int> tetPiece::lowestInEachCol(int direction)
{
	vector<vector<bool>> shape = getShape(direction);
	vector<int>lowest(4,4);
	for (int row = 3; row >= 0; row--)
		for (int col = 0; col < 4; col++) {
			if (shape[row][col])
				lowest[col] = row;
		}
	return lowest;
}

string tetPiece::getTypeName(pieceType type)
{
	switch (type) {
		case pieceType::ZPiece: return "Z";
		case pieceType::LPiece: return "L";
		case pieceType::OPiece: return "O";
		case pieceType::SPiece: return "S";
		case pieceType::IPiece: return "I";
		case pieceType::JPiece: return "J";
		case pieceType::TPiece: return "T";
	}
	cerr << "Invalid piece passed to getTypeName\n";
	exit(1);
}
pieceType tetPiece::parseType(string typeName)
{
	assert(typeName != "");

	switch (typeName[0]) {
		case 'z':
		case 'Z': return pieceType::ZPiece;
		case 'l':
		case 'L': return pieceType::LPiece;
		case 'o':
		case 'O': return pieceType::OPiece;
		case 's':
		case 'S': return pieceType::SPiece;
		case 'i':
		case 'I': return pieceType::IPiece;
		case 'j':
		case 'J': return pieceType::JPiece;
		case 't':
		case 'T': return pieceType::TPiece;
	}
	cerr << "invalid piecename parsed\n";
	exit(1);
}

pieceType tetPiece::	getType()
{
	return this->_type;
}

/**************/
/***tetBoard***/
/**************/

tetBoard::tetBoard(int width, int height)
{
	_width = width;
	_height = height;

	board.resize(width*height,false);
}

tetBoard::~tetBoard()
{
}

tetBoard::tetBoard(tetBoard *cpyBoard)
{
	_width = cpyBoard->getWidth();
	_height = cpyBoard->getHeight();
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
	board[getBoardIdx(x,y)] = val;
}

void tetBoard::emptyBoard()
{
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

tetGame::tetGame(int width, int height)
{
	board = new tetBoard(width,height);
}
void tetGame::reset()
{
	board->emptyBoard();
	holdFilled = false;
}

int tetGame::minX(pieceType type, int direction)
{
	tetPiece piece = tetPiece(type);
	vector<int> lowestInEachCol = piece.lowestInEachCol(direction);
	if (lowestInEachCol[1] == 4)
		return 0;
	if (lowestInEachCol[0] == 4)
		return 1;
	return 2;

}

int tetGame::maxX(pieceType type, int direction)
{
	tetPiece piece = tetPiece(type);
	vector<int> lowestInEachCol = piece.lowestInEachCol(direction);
	if (lowestInEachCol[3] == 4)
		return board->getWidth()-1;
	return board->getWidth()-2;

}

bool tetGame::inBounds(pieceType type, int direction, int x)
{
	return x <= maxX(type,direction) && x >= minX(type,direction);
}

int tetGame::findHitRow(pieceType type, int direction, int x)
{
	tetPiece piece = tetPiece(type);
	//leaving as an assertion for now
	assert(inBounds(type,direction,x));

	vector<int> lowestInEachCol = piece.lowestInEachCol(direction);
	int hitRow = 0;
	for (int relCol = 0; relCol < 4; relCol++) {
		int col = relCol-2+x;
		if (0<=col && col<board->getWidth()) {
			int colHeight = board->colHeight(col);
			if (lowestInEachCol[relCol] < 4) {
				int colHitRow = colHeight - lowestInEachCol[relCol]+2;
				hitRow = max(colHitRow,hitRow);
			}
		}
	}
	return hitRow;
}

//board modification
int tetGame::dropPiece(pieceType type, int direction, int x)
{
	int hitRow = findHitRow(type,direction,x);
	cout << hitRow << endl;
	tetPiece piece = tetPiece(type);
	vector<vector<bool>> shape = piece.getShape(direction);
	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			if (shape[row][col])
				board->setPieceAt(x+col-2,hitRow+row-2,true);
	return board->clearFullLines();
}

int tetGame::dropPiece(tetMove move)
{
	return dropPiece(move.type, move.direction, move.x);
}

boardInfo tetGame::getBoardInfo()
{
	return board->getBoardInfo();
}
boardInfo tetGame::testDrop(pieceType type, int direction, int x)
{
	tetBoard testBoard(board);
	//FIXME: copied code
	int hitRow = findHitRow(type,direction,x);
	tetPiece piece = tetPiece(type);
	vector<vector<bool>> shape = piece.getShape(direction);
	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			if (shape[row][col])
				testBoard.setPieceAt(x+col-2,hitRow+row-2,true);
	return testBoard.getBoardInfo();
}