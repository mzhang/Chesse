#ifndef MOVEDIAGPOS_H_
#define MOVEDIAGPOS_H_

#include <memory>
#include <vector>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class MoveDiagPos : public Decorator {
  int maxSteps;

public:
  MoveDiagPos(std::unique_ptr<Moveable>, int maxSteps = 1);

  std::vector<Move> getValidMoves(const GameState &, bool) const override;
  std::unique_ptr<Moveable> clone() const override;

  MoveDiagPos(const MoveDiagPos &);
};

#endif
