#ifndef MOVE_X_
#define MOVE_X_
#include <vector>
#include <memory>
#include "decorator.h"

class Board;
class Position;

class MoveX : public Decorator
{
    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(const Board &b) override;
    std::unique_ptr<Moveable> doClone() override;

public:
    explicit MoveX(std::unique_ptr<Moveable>);
    MoveX(const MoveX &);
};

#endif