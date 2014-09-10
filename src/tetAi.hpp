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
using namespace TetCore;

namespace TetAi {

	class tetAi
	{
	public:
		tetAi();
		~tetAi();
		tetMove chooseMove(tetGame* game, pieceType piece);
	private:
		double calculateValue(boardInfo info);
	};

}

#endif