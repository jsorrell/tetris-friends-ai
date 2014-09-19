#include "tetAi.hpp"
#include "tetConstants.hpp"
#include <vector>
#include <cfloat>

using namespace std;
using namespace Tetris;

struct tetAi::impl {
	static double calculateValue(boardInfo info)
	{
		if (info.toppedOut)
		 	return -100000.;
		double a = -0.66569;
		double b = 0.99275;
		double c = -0.46544;
		//double c = -3.;
		double d = -0.24077;
		//int linesClearedEquiv;
		// switch (info.fullLines) {
		// 	case 0:
		// 		linesClearedEquiv = 0.;
		// 		break;
		// 	case 1:
		// 		linesClearedEquiv = -3.;
		// 		break;
		// 	case 2:
		// 		linesClearedEquiv = 1.;
		// 		break;
		// 	case 3:
		// 		linesClearedEquiv = 20.;
		// 		break;
		// 	case 4:
		// 		linesClearedEquiv = 1000.;
		// 		break;
		// }
		return a*(double)info.aggHeight+b*(double)info.fullLines+c*(double)info.numHoles+d*(double)info.bumpiness;
	}
};

tetAi::tetAi(): pimpl(new impl)
{

}

tetAi::~tetAi()
{

}

bool tetAi::chooseMove(const tetGame &game, const tetPiece piece, tetMove *output)
{//TODO: allow use of hold on first piece
	int directionPriority[4] = {0,1,3,2};
	double curVal = -DBL_MAX;
	bool usingHold = false;
	tetPiece tryPiece = piece;
	for (int i = 0; i < 1; i++){
		/*if (i == 1){
			if (game.getHoldFilled() && tryPiece != game.getHoldPiece()) {
					tryPiece = game.getHoldPiece();
				} else break;
		}*/
		for (int d = 0; d<4; d++) {
			int direction = directionPriority[d];
			int minX = game.minX(tryPiece,direction);
			int maxX = game.maxX(tryPiece,direction);
			for (int x = minX; x <= maxX; x++) {
				boardInfo info = game.testDrop(tryPiece,direction,x);
				double value = impl::calculateValue(info);
				if (value > curVal) {
					curVal = value;
					output->piece = tryPiece;
					output->direction = direction;
					output->x = x;
					//if (i == 1)
						//usingHold = true;
				}
			}
		}
	}
	return usingHold;
}