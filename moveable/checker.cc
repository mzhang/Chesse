#include <memory>
#include <vector>

#include "../data/move.h"
#include "../data/pieceType.h"
#include "../data/playerColor.h"
#include "../game/gameState.h"
#include "./moveable.h"
#include "./piece.h"
#include "checker.h"
#include "decorator.h"

using namespace std;

Checker::Checker(unique_ptr<Moveable> component, int promotionRank)
    : Decorator{std::move(component)}, promotionRank{promotionRank},
      isPromoted{false} {}

Checker::Checker(const Checker &o)
    : Decorator{o}, promotionRank{o.promotionRank}, isPromoted{o.isPromoted} {}

vector<Position> Checker::getAttackedTiles(const GameState &g, bool) const {
  Position currentPos = Decorator::getPosition();
  vector<Position> tiles = Decorator::getAttackedTiles(g, true);
  int forwardsDir = (Decorator::getOwner() == PlayerColor::WHITE) ? 1 : -1;
  tiles.emplace_back(Position{currentPos.x - 1, currentPos.y + forwardsDir});
  tiles.emplace_back(Position{currentPos.x + 1, currentPos.y + forwardsDir});
  return tiles;
}

vector<Move> Checker::getValidMoves(const GameState &g,
                                    bool checkChildren) const {
  vector<Move> moves{};
  PlayerColor player = Decorator::getOwner();
  Position currentPos = Decorator::getPosition();

  if (checkChildren) {
    moves = Decorator::getValidMoves(g, true);
  }

  int moveDirection = (player == PlayerColor::WHITE) ? 1 : -1;
  Position leftDiag = Position{currentPos.x - 1, currentPos.y + moveDirection};
  Position rightDiag = Position{currentPos.x + 1, currentPos.y + moveDirection};

  if (g.isInBounds(leftDiag) && g.isEmpty(leftDiag)) {
    moves.emplace_back(Move{currentPos, leftDiag});
  }

  if (g.isInBounds(rightDiag) && g.isEmpty(rightDiag)) {
    moves.emplace_back(Move{currentPos, rightDiag});
  }

  Position leftDiag2 =
      Position{currentPos.x - 2, currentPos.y + 2 * moveDirection};
  Position rightDiag2 =
      Position{currentPos.x + 2, currentPos.y + 2 * moveDirection};

  if (g.isInBounds(leftDiag) && !g.isEmpty(leftDiag) &&
      !g.isOwner(leftDiag, player) && g.isInBounds(leftDiag2) &&
      g.isEmpty(leftDiag2)) {
    moves.emplace_back(Move{currentPos, leftDiag2, leftDiag});
  }

  if (g.isInBounds(rightDiag) && !g.isEmpty(rightDiag) &&
      !g.isOwner(rightDiag, player) && g.isInBounds(rightDiag2) &&
      g.isEmpty(rightDiag2)) {
    moves.emplace_back(Move{currentPos, rightDiag2, rightDiag});
  }

  if (isPromoted) {
    moveDirection = -moveDirection;
    Position leftDiag =
        Position{currentPos.x - 1, currentPos.y + moveDirection};
    Position rightDiag =
        Position{currentPos.x + 1, currentPos.y + moveDirection};

    if (g.isInBounds(leftDiag) && g.isEmpty(leftDiag)) {
      moves.emplace_back(Move{currentPos, leftDiag});
    }

    if (g.isInBounds(rightDiag) && g.isEmpty(rightDiag)) {
      moves.emplace_back(Move{currentPos, rightDiag});
    }

    Position leftDiag2 =
        Position{currentPos.x - 2, currentPos.y + 2 * moveDirection};
    Position rightDiag2 =
        Position{currentPos.x + 2, currentPos.y + 2 * moveDirection};

    if (g.isInBounds(leftDiag) && !g.isEmpty(leftDiag) &&
        !g.isOwner(leftDiag, player) && g.isInBounds(leftDiag2) &&
        g.isEmpty(leftDiag2)) {
      moves.emplace_back(Move{currentPos, leftDiag2, leftDiag});
    }

    if (g.isInBounds(rightDiag) && !g.isEmpty(rightDiag) &&
        !g.isOwner(rightDiag, player) && g.isInBounds(rightDiag2) &&
        g.isEmpty(rightDiag2)) {
      moves.emplace_back(Move{currentPos, rightDiag2, rightDiag});
    }
  }

  return moves;
}

void Checker::onMove(const Move &m, const Position &newPos, bool checkChildren,
                     int movedCountDelta) {
  if (!isPromoted && newPos.y == promotionRank) {
    isPromoted = true;
  }
  Decorator::onMove(m, newPos, checkChildren, movedCountDelta);
}

unique_ptr<Moveable> Checker::clone() const {
  return make_unique<Checker>(*this);
}
