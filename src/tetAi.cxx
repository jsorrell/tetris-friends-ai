#include "tetAi.hpp"

using namespace TetAi;

tetAi::tetAi()
{

}

tetAi::~tetAi()
{

}

double tetAi::calculateValue(boardInfo info)
{
	double a = -0.66569;
	double b = 0.99275;
	double c = -0.46544;
	double d = -0.24077;
	return a*(double)info.aggHeight+b*(double)info.fullLines+c*(double)info.numHoles+d*(double)info.bumpiness;
}

tetMove tetAi::chooseMove(tetGame* game, pieceType piece)
{
	int directionPriority[4] = {0,1,3,2};
	double curVal = -DBL_MAX;
	tetMove move;
	for (int d = 0; d<4; d++) {
		int direction = directionPriority[d];
		int minX = game->minX(piece,direction);
		int maxX = game->maxX(piece,direction);
		for (int x = minX; x <= maxX; x++) {
			boardInfo info = game->testDrop(piece,direction,x);
			double value = calculateValue(info);
			if (value > curVal) {
				curVal = value;
				move.type = piece;
				move.direction = direction;
				move.x = x;
			}
		}

	}
	return move;
}