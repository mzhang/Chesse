#ifndef CASTLE_H_
#define CASTLE_H_

#include <vector>
#include <memory>

#include "decorator.h"
#include "../data/position.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

struct Castle : public Decorator
{
    std::vector<Position> partnerPositions;

public:
    Castle(std::unique_ptr<Moveable>, std::vector<Position>);
    Castle(const Castle &);

    std::vector<Move> getValidMoves(const GameState &) const override;
    std::unique_ptr<Moveable> clone() const override;
};

#endif