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
    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;
};

#endif