#ifndef MOVE_X_H_
#define MOVE_X_H_

#include <memory>
#include <vector>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class MoveX : public Decorator {
  int maxSteps;

public:
  MoveX(std::unique_ptr<Moveable>, int maxSteps = 1);

  std::vector<Move> getValidMoves(const GameState &, bool) const override;
  std::unique_ptr<Moveable> clone() const override;

  MoveX(const MoveX &);
};

#endif
