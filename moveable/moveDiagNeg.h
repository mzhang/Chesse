#ifndef MOVEDIAGNEG_H_
#define MOVEDIAGNEG_H_

#include <memory>
#include <vector>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class MoveDiagNeg : public Decorator {
  int maxSteps;

public:
  MoveDiagNeg(std::unique_ptr<Moveable>, int maxSteps = 1);

  std::vector<Move> getValidMoves(const GameState &, bool) const override;
  std::unique_ptr<Moveable> clone() const override;

  MoveDiagNeg(const MoveDiagNeg &);
};

#endif
