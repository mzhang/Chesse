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

    PieceType getPieceType() override;
    std::vector<Move> getValidMoves(const GameState &) override;
    std::unique_ptr<Moveable> clone() override;

    MoveZ(const MoveZ &);
};

#endif