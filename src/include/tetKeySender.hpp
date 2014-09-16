#ifndef __TET_KEY_SENDER_H__
#define __TET_KEY_SENDER_H__

#include <memory>

namespace Tetris
{

class tetKeySender
{
public:
	tetKeySender();
	tetKeySender(const tetKeySender&);
  ~tetKeySender();
	void dropPiece(int rotation, int col);
	void swapHold();
private:
	struct impl; std::unique_ptr<impl> pimpl;
};
}
#endif