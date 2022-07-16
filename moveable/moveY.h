#ifndef MOVE_Y_
#define MOVE_Y_
#include <vector>
#include <memory>
#include "decorator.h"

class Board;
class Position;

class MoveY : public Decorator
{
public:
    explicit MoveY(std::unique_ptr<Moveable>);

    PieceType getPieceType() override;
    std::vector<Move> getValidMoves(const GameState &) override;
    std::unique_ptr<Moveable> clone() override;

    MoveY(const MoveY &);
};

#endif