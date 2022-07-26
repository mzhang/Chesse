#ifndef CASTLE_H_
#define CASTLE_H_

#include <memory>
#include <vector>

#include "../data/position.h"
#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class Castle : public Decorator {
  std::vector<Position> partnerPositions;

public:
  std::vector<Position> getAttackedTiles(const GameState &,
                                         bool) const override;
  Castle(std::unique_ptr<Moveable>, std::vector<Position>);
  Castle(const Castle &);

  std::vector<Move> getValidMoves(const GameState &, bool) const override;
  std::unique_ptr<Moveable> clone() const override;
};

#endif
