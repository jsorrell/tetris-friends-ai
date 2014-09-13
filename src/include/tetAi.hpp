#ifndef _TETAI_H_
#define _TETAI_H_

/*TODO: Only looks at next piece */

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cfloat>
#include "tetCore.hpp"

using namespace std;
using namespace Tetris;

namespace Tetris {

	class tetAi
	{
	public:
		static bool chooseMove(const tetGame &game, const tetPiece piece, tetMove *output);

	private:
		static double calculateValue(boardInfo info);
	};

}

#endif