#ifndef MOVE_X_
#define MOVE_X_
#include <vector>
#include <memory>
#include "decorator.h"

class Board;
class Position;

class MoveX : public Decorator
{
public:
    explicit MoveX(std::unique_ptr<Moveable>);
    MoveX(const MoveX &);

    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;

    std::unique_ptr<Moveable> clone() override;
};

#endif