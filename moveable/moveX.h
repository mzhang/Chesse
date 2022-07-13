#ifndef MOVE_X_
#define MOVE_X_

#include <vector>
#include "decorator.h"

class Board;
class Position;

class MoveX : public Decorator
{
    std::vector<Position> getDelta() override;
    std::vector<Position> getValidMoves(Board b) override;
};

#endif