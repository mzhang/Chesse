#ifndef MOVE_L_
#define MOVE_L_
#include <vector>
#include <memory>
#include "decorator.h"

class Board;
class Position;

class MoveL : public Decorator
{
    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(const Board &b) override;
    std::unique_ptr<Moveable> doClone() override;

public:
    explicit MoveL(std::unique_ptr<Moveable>);
    MoveL(const MoveL &);
};

#endif