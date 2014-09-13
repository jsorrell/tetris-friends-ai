#ifndef _TETPIECES_H_
#define _TETPIECES_H_

#include <vector>
#include <string>
#include "tetRandom.hpp"
#include "tetCore.hpp"

using namespace TetCore;

class tetPieces {
public:
  tetPieces(int seed);
  tetPiece getNextPiece();
  std::vector<tetPiece> getNextPieces(unsigned num);
private:
    RandomPieceGen* rand;
    std::vector<tetPiece> pieceQueue;
    string pieceMap[7] = {"Z","L","O","S","I","J","T"};
};


#endif
