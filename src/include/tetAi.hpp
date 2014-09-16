#ifndef _TETAI_H_
#define _TETAI_H_

#include <memory>
#include "tetCore.hpp"

namespace Tetris {

	class tetAi
	{
	public:
		tetAi();
		~tetAi();
		static bool chooseMove(const tetGame &game, const tetPiece piece, tetMove *output);

	private:
		struct impl; std::unique_ptr<impl> pimpl;
	};

}

#endif