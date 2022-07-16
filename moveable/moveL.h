#ifndef MOVE_L_
#define MOVE_L_
#include <vector>
#include <memory>
#include "decorator.h"

class Board;
class Position;

class MoveL : public Decorator
{
public:
    explicit MoveL(std::unique_ptr<Moveable>);

    PieceType getPieceType() override;
    std::vector<Move> getValidMoves(const GameState &) override;
    std::unique_ptr<Moveable> clone() override;

    MoveL(const MoveL &);
};

#endif