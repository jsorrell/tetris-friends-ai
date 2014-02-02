#include "tetPieces.hpp"

using namespace std;


tetPieces :: tetPieces(int seed) {
  this->rand = new RandomPieceGen(seed);
}

tetPiece tetPieces :: getNextPiece() {
  if (pieceQueue.empty()) {
    bool refillSlots[7];
    
    for (int i = 0; i < 7; i++) {
      refillSlots[i] = false;
    }
    
    tetPiece p;
    for (int i = 0; i < 7; i++) {
      do {
        p = (tetPiece)(this->rand->GetNextRandom() % 7);
      } while (refillSlots[p]);
      
      refillSlots[p] = true;
      pieceQueue.insert(pieceQueue.begin(),p);
    }
  }
  tetPiece back = pieceQueue.back();
  
  pieceQueue.pop_back();
  
  return back;
}

vector<tetPiece> tetPieces :: getNextPieces(unsigned num) {
  vector<tetPiece> output;
  for (int i = num; i > 0; i--) {
    output.push_back(this->getNextPiece());
  }
  return output;
}



//tetPiece *getNext7Pieces(RandomPieceGen r) {
//  tetPiece pieceArray[7] = {0,1,2,3,4,5,6};
//  bool refillSlots[7];
//  tetPiece *output = new tetPiece[7];
//  
//  for (int i = 0; i < 7; i++) {
//    refillSlots[i] = false;
//  }
//  tetPiece p;
//  for (int i = 0; i < 7; i++) {
//    do {
//      p = r.GetNextRandom() % 7;
//    
//    } while (refillSlots[j]);
//    
//    refillSlots[p] = true;
//    
//    output[i] = p;
//  }
//  return output;
//}

string getName(tetPiece p) {
  switch(p) {
    case (0):
      return "Z";
    case (1):
      return "L";
    case (2):
      return "O";
    case (3):
      return "S";
    case (4):
      return "I";
    case (5):
      return "J";
    case (6):
      return "T";
    default:
      return "This is not a piece";
  }
}
