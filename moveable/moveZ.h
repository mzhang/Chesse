#ifndef MOVE_Z_
#define MOVE_Z_
#include <vector>
#include "decorator.h"

class Board;
class Position;

class MoveZ : public Decorator
{
public:
    MoveZ(Moveable *component);
    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;
};

#endif