#include <memory>
#include <vector>

#include "../data/move.h"
#include "../data/pieceType.h"
#include "../data/playerColor.h"
#include "../game/gameState.h"
#include "./moveable.h"
#include "./piece.h"
#include "decorator.h"
#include "nuke.h"

using namespace std;

Nuke::Nuke(unique_ptr<Moveable> component) : Decorator{std::move(component)} {}

Nuke::Nuke(const Nuke &o) : Decorator{o} {}

vector<Move> Nuke::getValidMoves(const GameState &g, bool checkChildren) const {
  vector<Move> moves{};

  if (checkChildren) {
    moves = Decorator::getValidMoves(g, true);
  }

  vector<Move> nukeMoves{};
  for (const Move &move : moves) {
    Move nukeMove{move.from, move.to, move.capturePositions};
    for (const Position &pos : move.capturePositions) {
      for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
          Position nukePos{pos.x + i, pos.y + j};
          if (g.isInBounds(nukePos) && !g.isEmpty(nukePos)) {
            nukeMove.capturePositions.push_back(nukePos);
          }
        }
      }
    }
    nukeMoves.push_back(nukeMove);
  }

  // moves are appended, not a union. must remove duplicates
  return nukeMoves;
}

unique_ptr<Moveable> Nuke::clone() const { return make_unique<Nuke>(*this); }
