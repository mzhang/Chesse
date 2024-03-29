#include <memory>
#include <vector>

#include "../data/move.h"
#include "../data/pieceType.h"
#include "../data/playerColor.h"
#include "../game/gameState.h"
#include "./moveable.h"
#include "./piece.h"
#include "decorator.h"
#include "moveY.h"

using namespace std;

MoveY::MoveY(unique_ptr<Moveable> component, int maxSteps)
    : Decorator{std::move(component)}, maxSteps{maxSteps} {}

vector<Move> MoveY::getValidMoves(const GameState &g,
                                  bool checkChildren) const {
  vector<Move> moves{};
  if (checkChildren) {
    moves = Decorator::getValidMoves(g, true);
  }
  PlayerColor player = Decorator::getOwner();

  Position currentPos = getPosition();
  Position pos = currentPos;

  ++pos.y;
  while (g.isInBounds(pos) && (abs(pos.y - currentPos.y) <= maxSteps)) {
    if (g.isEmpty(pos)) {
      moves.push_back(Move{currentPos, pos});
    } else if (!g.isOwner(pos, player)) {
      moves.push_back(Move{currentPos, pos, pos});
      break;
    } else {
      break;
    }
    ++pos.y;
  }

  pos = currentPos;
  --pos.y;
  while (g.isInBounds(pos) && (abs(pos.y - currentPos.y) <= maxSteps)) {
    if (g.isEmpty(pos)) {
      moves.push_back(Move{currentPos, pos});
    } else if (!g.isOwner(pos, player)) {
      moves.push_back(Move{currentPos, pos, pos});
      break;
    } else {
      break;
    }
    --pos.y;
  }
  // moves are appended, not a union. must remove duplicates
  return moves;
}

unique_ptr<Moveable> MoveY::clone() const { return make_unique<MoveY>(*this); }

MoveY::MoveY(const MoveY &o) : Decorator{o}, maxSteps{o.maxSteps} {}
