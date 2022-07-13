#ifndef MOVE_X_
#define MOVE_X_

#include <vector>
#include "decorator.h"

class Board;
class Position;

class MoveX : public Decorator
{
    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;
};

#endif