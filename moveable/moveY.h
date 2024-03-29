#ifndef MOVE_Y_H_
#define MOVE_Y_H_

#include <memory>
#include <vector>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class MoveY : public Decorator {
  int maxSteps;

public:
  MoveY(std::unique_ptr<Moveable>, int maxSteps = 1);

  std::vector<Move> getValidMoves(const GameState &, bool) const override;
  std::unique_ptr<Moveable> clone() const override;

  MoveY(const MoveY &);
};

#endif
