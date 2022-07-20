#ifndef MOVE_X_H_
#define MOVE_X_H_

#include <vector>
#include <memory>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

struct MoveX : public Decorator
{
    int maxSteps;

public:
    MoveX(std::unique_ptr<Moveable>, int maxSteps = 1);

    std::vector<Move> getValidMoves(const GameState &) override;
    std::unique_ptr<Moveable> clone() override;

    MoveX(const MoveX &);
};

#endif