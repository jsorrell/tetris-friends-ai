#ifndef _TETRANDOM_H_
#define _TETRANDOM_H_
class RandomPieceGen {

  public:
    RandomPieceGen(int seed);
    int getSeed() { return mSeed; }
    int getNextRandom();

  private:
    int mRand1;
    int mRand2;
    int mRandBuffer[17];
    int mSeed;
};

#endif
