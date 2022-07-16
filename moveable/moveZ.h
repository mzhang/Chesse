#ifndef MOVE_Z_
#define MOVE_Z_
#include <vector>
#include <memory>
#include "decorator.h"

class Board;
class Position;

class MoveZ : public Decorator
{
public:
    MoveZ(std::unique_ptr<Moveable>);
    MoveZ(const MoveZ &);

    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;

    std::unique_ptr<Moveable> clone() override;
};

#endif