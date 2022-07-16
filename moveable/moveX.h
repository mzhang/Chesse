#ifndef MOVE_X_
#define MOVE_X_
#include <vector>
#include <memory>
#include "decorator.h"

enum class PieceType;
class GameState;
class Move;

class MoveX : public Decorator
{
    int maxSteps;

public:
    MoveX(std::unique_ptr<Moveable>);

    PieceType getPieceType() override;
    std::vector<Move> getValidMoves(const GameState &) override;
    std::unique_ptr<Moveable> clone() override;

    MoveX(const MoveX &);
};

#endif