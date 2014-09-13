#include "tetRandom.hpp"

using namespace std;

//PLEASE don't modify this

RandomPieceGen :: RandomPieceGen(int seed) {
  mSeed = seed & 0xFFFF;
  unsigned m = (unsigned)mSeed;
  for (int i = 0; i < 17; i++) {
    mRandBuffer[i] = m;
    m = (((m << 5 & 0xFFFF) | (m >> 11 & 0xFFFF)) & 0xFFFF) + 97;
    m &= 0xFFFF;
  }

  mRand1 = 0;
  mRand2 = 10;

  for (int i = 0; i < 100; i++) {
    this->getNextRandom();
  }
}

int RandomPieceGen :: getNextRandom()
{
  int b = mRandBuffer[mRand1];
  int c = mRandBuffer[mRand2];

  int a = ((b << 3 & 0xFFFF) | (b >> 13 & 0xFFFF)) & 0xFFFF;
  a += ((c << 5 & 0xFFFF) | (c >> 11 & 0xFFFF)) & 0xFFFF;
  a &= 0xFFFF;
  mRandBuffer[this->mRand1] = a;
  mRand1 = mRand1 <= 0 ? 16 : mRand1-1;
  mRand2 = mRand2 <= 0 ? 16 : mRand2-1;
  return a & 2047u;
}
