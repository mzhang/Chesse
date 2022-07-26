#ifndef GOLEM_H_
#define GOLEM_H_

#include <memory>
#include <vector>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class Golem : public Decorator {
  int maxMoves;
  bool isBroken;

public:
  Golem(std::unique_ptr<Moveable>, int);
  Golem(const Golem &);

  std::vector<Move> getValidMoves(const GameState &, bool) const override;
  std::unique_ptr<Moveable> clone() const override;
  void onMove(const Move &, const Position &, bool, int) override;
};

#endif
