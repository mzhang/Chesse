#ifndef BRICK_H_
#define BRICK_H_

#include <vector>
#include <memory>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class Brick : public Decorator
{
public:
    explicit Brick(std::unique_ptr<Moveable>);
    Brick(const Brick &);

    std::vector<Move> getValidMoves(const GameState &, bool) const override;
    std::unique_ptr<Moveable> clone() const override;
};

#endif