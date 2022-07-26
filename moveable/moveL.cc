#include <memory>
#include <vector>

#include "../data/move.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "./moveable.h"
#include "./piece.h"
#include "decorator.h"
#include "moveL.h"

using namespace std;

MoveL::MoveL(unique_ptr<Moveable> component)
    : Decorator{std::move(component)} {}

vector<Move> MoveL::getValidMoves(const GameState &g,
                                  bool checkChildren) const {
  vector<Move> moves{};
  if (checkChildren) {
    moves = Decorator::getValidMoves(g, true);
  }
  PlayerColor player = Decorator::getOwner();

  Position currentPos = getPosition();

  Position topLeft = Position{currentPos.x - 1, currentPos.y + 2};
  if (g.isInBounds(topLeft)) {
    if (g.isEmpty(topLeft)) {
      moves.push_back(Move{currentPos, topLeft});
    } else if (!g.isOwner(topLeft, player)) {
      moves.push_back(Move{currentPos, topLeft, topLeft});
    }
  }

  Position topRight = Position{currentPos.x + 1, currentPos.y + 2};
  if (g.isInBounds(topRight)) {
    if (g.isEmpty(topRight)) {
      moves.push_back(Move{currentPos, topRight});
    } else if (!g.isOwner(topRight, player)) {
      moves.push_back(Move{currentPos, topRight, topRight});
    }
  }

  Position middleTopRight = Position{currentPos.x + 2, currentPos.y + 1};
  if (g.isInBounds(middleTopRight)) {
    if (g.isEmpty(middleTopRight)) {
      moves.push_back(Move{currentPos, middleTopRight});
    } else if (!g.isOwner(middleTopRight, player)) {
      moves.push_back(Move{currentPos, middleTopRight, middleTopRight});
    }
  }

  Position middleBottomRight = Position{currentPos.x + 2, currentPos.y - 1};
  if (g.isInBounds(middleBottomRight)) {
    if (g.isEmpty(middleBottomRight)) {
      moves.push_back(Move{currentPos, middleBottomRight});
    } else if (!g.isOwner(middleBottomRight, player)) {
      moves.push_back(Move{currentPos, middleBottomRight, middleBottomRight});
    }
  }

  Position bottomRight = Position{currentPos.x + 1, currentPos.y - 2};
  if (g.isInBounds(bottomRight)) {
    if (g.isEmpty(bottomRight)) {
      moves.push_back(Move{currentPos, bottomRight});
    } else if (!g.isOwner(bottomRight, player)) {
      moves.push_back(Move{currentPos, bottomRight, bottomRight});
    }
  }

  Position bottomLeft = Position{currentPos.x - 1, currentPos.y - 2};
  if (g.isInBounds(bottomLeft)) {
    if (g.isEmpty(bottomLeft)) {
      moves.push_back(Move{currentPos, bottomLeft});
    } else if (!g.isOwner(bottomLeft, player)) {
      moves.push_back(Move{currentPos, bottomLeft, bottomLeft});
    }
  }

  Position middleBottomLeft = Position{currentPos.x - 2, currentPos.y - 1};
  if (g.isInBounds(middleBottomLeft)) {
    if (g.isEmpty(middleBottomLeft)) {
      moves.push_back(Move{currentPos, middleBottomLeft});
    } else if (!g.isOwner(middleBottomLeft, player)) {
      moves.push_back(Move{currentPos, middleBottomLeft, middleBottomLeft});
    }
  }

  Position middleTopLeft = Position{currentPos.x - 2, currentPos.y + 1};
  if (g.isInBounds(middleTopLeft)) {
    if (g.isEmpty(middleTopLeft)) {
      moves.push_back(Move{currentPos, middleTopLeft});
    } else if (!g.isOwner(middleTopLeft, player)) {
      moves.push_back(Move{currentPos, middleTopLeft, middleTopLeft});
    }
  }

  return moves;
}

unique_ptr<Moveable> MoveL::clone() const { return make_unique<MoveL>(*this); }

MoveL::MoveL(const MoveL &o) : Decorator{o} {}
