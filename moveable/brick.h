#ifndef BRICK_H_
#define BRICK_H_

#include <memory>
#include <vector>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class Brick : public Decorator {
public:
  explicit Brick(std::unique_ptr<Moveable>);
  Brick(const Brick &);

  std::vector<Position> getAttackedTiles(const GameState &,
                                         bool) const override;
  std::vector<Move> getValidMoves(const GameState &, bool) const override;
  std::unique_ptr<Moveable> clone() const override;
};

#endif
