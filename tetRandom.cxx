#include "tetRandom.hpp"

using namespace std;

RandomPieceGen :: RandomPieceGen(int seed) {
  this->mSeed = seed & 0xFFFF;
  unsigned m = (unsigned)mSeed;
  for (int i = 0; i < 17; i++) {
    this->mRandBuffer[i] = m;
    m = (((m << 5 & 0xFFFF) | (m >> 11 & 0xFFFF)) & 0xFFFF) + 97;
    m &= 0xFFFF;
  }
  
  mRand1 = 0;
  mRand2 = 10;

  for (int i = 0; i < 100; i++) {
    this->GetNextRandom();
  }
}

int RandomPieceGen :: GetNextRandom() {
  int a;
  int b;
  int c;

  b = this->mRandBuffer[this->mRand1];
  c = this->mRandBuffer[this->mRand2];

  a = ((b << 3 & 0xFFFF) | (b >> 13 & 0xFFFF)) & 0xFFFF;
  a += ((c << 5 & 0xFFFF) | (c >> 11 & 0xFFFF)) & 0xFFFF;
  a &= 0xFFFF;
  this->mRandBuffer[this->mRand1] = a;
  this->mRand1 = this->mRand1 <= 0 ? 16 : this->mRand1-1;
  this->mRand2 = this->mRand2 <= 0 ? 16 : this->mRand2-1;
  return a & 2047u;
}
