#ifndef __TET_PLAYER_H__
#define __TET_PLAYER_H__
#include <string>
#include <memory>

namespace Tetris {
class tetPlayer
{
public:
	tetPlayer(const std::string interface);
	~tetPlayer();
	void go();

private:
	struct impl; std::unique_ptr<impl> pimpl;
};
}
#endif