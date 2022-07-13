#ifndef MOVE_Y_
#define MOVE_Y_
#include <vector>
#include "decorator.h"

class Board;
class Position;

class MoveY : public Decorator
{
public:
    MoveY(Moveable *component);
    MoveY(const MoveY &);

    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;

    std::unique_ptr<Moveable> clone() override;
};

#endif