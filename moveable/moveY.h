#ifndef MOVE_Y_H_
#define MOVE_Y_H_

#include <vector>
#include <memory>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

struct MoveY : public Decorator
{
    int maxSteps;

public:
    MoveY(std::unique_ptr<Moveable>, int maxSteps = 1);

    std::vector<Move> getValidMoves(const GameState &) override;
    std::unique_ptr<Moveable> clone() override;

    MoveY(const MoveY &);
};

#endif