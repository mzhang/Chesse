#ifndef MOVE_L_
#define MOVE_L_
#include <vector>
#include "decorator.h"

class Board;
class Position;

class MoveL : public Decorator
{
public:
    MoveL(Moveable *component);
    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;
};

#endif