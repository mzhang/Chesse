#ifndef MOVE_L_
#define MOVE_L_
#include <vector>
#include "decorator.h"

class Board;
class Position;

class MoveL : public Decorator
{
    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;
    std::unique_ptr<Moveable> doClone() override;

public:
    MoveL(Moveable *component);
    MoveL(const MoveL &);
};

#endif