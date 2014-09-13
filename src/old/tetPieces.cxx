#include "tetPieces.hpp"

using namespace std;


tetPieces::tetPieces(int seed) {
  this->rand = new RandomPieceGen(seed);
}

tetPiece tetPieces::getNextPiece() {
  if (pieceQueue.empty()) {
    vector<bool> refillSlots(7,false);

    //create bag of 7 pieces
    for (int i = 0; i < 7; i++) {
      //keep picking until get one that has not been picked yet.
      tetPiece p;
      do {
        p = (tetPiece)(this->rand->getNextRandom() % 7);
      } while (refillSlots[p]);
      //found one not made yet
      refillSlots[p] = true;
      //put in queue
      pieceQueue.insert(pieceQueue.begin(),p);
    }
  }
  tetPiece back = pieceQueue.back();

  pieceQueue.pop_back();

  return back;
}

vector<tetPiece> tetPieces::getNextPieces(unsigned num) {
  vector<tetPiece> output;
  for (int i = num; i > 0; i--) {
    output.push_back(this->getNextPiece());
  }
  return output;
}