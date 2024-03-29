#include <cstdlib>
#include <memory>
#include <vector>

#include "../data/move.h"
#include "../data/pieceType.h"
#include "../data/playerColor.h"
#include "../game/gameState.h"
#include "./moveable.h"
#include "./piece.h"
#include "decorator.h"
#include "moveX.h"

using namespace std;

MoveX::MoveX(unique_ptr<Moveable> component, int maxSteps)
    : Decorator{std::move(component)}, maxSteps{maxSteps} {}

vector<Move> MoveX::getValidMoves(const GameState &g,
                                  bool checkChildren) const {
  vector<Move> moves{};
  if (checkChildren) {
    moves = Decorator::getValidMoves(g, true);
  }

  PlayerColor playerColor = Decorator::getOwner();
  Position currentPos = getPosition();
  Position pos = currentPos;

  ++pos.x;
  while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps)) {
    if (g.isEmpty(pos)) {
      moves.push_back(Move{currentPos, pos});
    } else if (!g.isOwner(pos, playerColor)) {
      moves.push_back(Move{currentPos, pos, pos});
      break;
    } else {
      break;
    }
    ++pos.x;
  }

  pos = currentPos;
  --pos.x;
  while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps)) {
    if (g.isEmpty(pos)) {
      moves.push_back(Move{currentPos, pos});
    } else if (!g.isOwner(pos, playerColor)) {
      moves.push_back(Move{currentPos, pos, pos});
      break;
    } else {
      break;
    }
    --pos.x;
  }
  // moves are appended, not a union. must remove duplicates
  return moves;
}

unique_ptr<Moveable> MoveX::clone() const { return make_unique<MoveX>(*this); }

MoveX::MoveX(const MoveX &o) : Decorator{o}, maxSteps{o.maxSteps} {}
