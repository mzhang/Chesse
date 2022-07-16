#ifndef MOVE_Y_
#define MOVE_Y_
#include <vector>
#include <memory>
#include "decorator.h"

class Board;
class Position;

class MoveY : public Decorator
{
    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(const Board &b) override;
    std::unique_ptr<Moveable> doClone() override;

public:
    explicit MoveY(std::unique_ptr<Moveable>);
    MoveY(const MoveY &);
};

#endif