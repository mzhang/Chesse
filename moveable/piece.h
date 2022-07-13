#ifndef MOVEABLES_H_
#define MOVEABLES_H_
#include <vector>
#include "moveable.h"

class Position;
class Board;

class Piece : public Moveable
{
    virtual std::vector<Position> getDelta() override;
    virtual std::vector<Position> getValidMoves(Board b) override;

public:
    Piece();
    virtual ~Piece();
};
#endif