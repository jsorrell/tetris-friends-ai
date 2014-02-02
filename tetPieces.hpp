#ifndef _TETPIECES_H_
#define _TETPIECES_H_

#include <vector>
#include <string>
#include "tetRandom.hpp"


enum tetPiece{ZPiece,LPiece,OPiece,SPiece,IPiece,JPiece,TPiece};

std::string getName(tetPiece p);

class tetPieces {
    RandomPieceGen* rand;
    std::vector<tetPiece> pieceQueue;

  public:
    tetPieces(int seed);
    tetPiece getNextPiece();
    std::vector<tetPiece> getNextPieces(unsigned num);
};


#endif
