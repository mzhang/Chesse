#include <vector>
#include <memory>

#include "moveL.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"

using namespace std;

MoveL::MoveL(unique_ptr<Moveable> component) : Decorator{std::move(component)} {}

vector<Move> MoveL::getValidMoves(const GameState &g) const
{
    vector<Move> moves = Decorator::getValidMoves(g);
    PlayerColor player = Decorator::getOwner();

    Position currentPos = getPosition();
 
    Position topLeft = Position{currentPos.x-1, currentPos.y+2};
    if (g.isInBounds(topLeft)) {
        if (!g.isOwner(topLeft, player)) {
            moves.push_back(Move{currentPos, topLeft, topLeft});
        } else if (g.isEmpty(topLeft)) {
            moves.push_back(Move{currentPos, topLeft});
        }
    }

    Position topRight = Position{currentPos.x+1, currentPos.y+2};
    if (g.isInBounds(topRight)) {
        if (!g.isOwner(topRight, player)) {
            moves.push_back(Move{currentPos, topRight, topRight});
        } else if (g.isEmpty(topRight)) {
            moves.push_back(Move{currentPos, topRight});
        }
    }

    Position middleTopRight = Position{currentPos.x+2, currentPos.y+1};
    if (g.isInBounds(middleTopRight)) {
        if (!g.isOwner(middleTopRight, player)) {
            moves.push_back(Move{currentPos, middleTopRight, middleTopRight});
        } else if (g.isEmpty(middleTopRight)) {
            moves.push_back(Move{currentPos, middleTopRight});
        }
    }

    Position middleBottomRight = Position{currentPos.x+2, currentPos.y-1};
    if (g.isInBounds(middleBottomRight)) {
        if (!g.isOwner(middleBottomRight, player)) {
            moves.push_back(Move{currentPos, middleBottomRight, middleBottomRight});
        } else if (g.isEmpty(middleBottomRight)) {
            moves.push_back(Move{currentPos, middleBottomRight});
        }
    }

    Position bottomRight = Position{currentPos.x+1, currentPos.y-2};
    if (g.isInBounds(bottomRight)) {
        if (!g.isOwner(bottomRight, player)) {
            moves.push_back(Move{currentPos, bottomRight, bottomRight});
        } else if (g.isEmpty(bottomRight)) {
            moves.push_back(Move{currentPos, bottomRight});
        }
    }

    Position bottomLeft = Position{currentPos.x-1, currentPos.y-2};
    if (g.isInBounds(bottomLeft)) {
        if (!g.isOwner(bottomLeft, player)) {
            moves.push_back(Move{currentPos, bottomLeft, bottomLeft});
        } else if (g.isEmpty(bottomLeft)) {
            moves.push_back(Move{currentPos, bottomLeft});
        }
    }

    Position middleBottomLeft = Position{currentPos.x-2, currentPos.y-1};
    if (g.isInBounds(middleBottomLeft)) {
        if (!g.isOwner(middleBottomLeft, player)) {
            moves.push_back(Move{currentPos, middleBottomLeft, middleBottomLeft});
        } else if (g.isEmpty(middleBottomLeft)) {
            moves.push_back(Move{currentPos, middleBottomLeft});
        }
    }

    Position middleTopLeft = Position{currentPos.x-2, currentPos.y+1};
    if (g.isInBounds(middleTopLeft)) {
        if (!g.isOwner(middleTopLeft, player)) {
            moves.push_back(Move{currentPos, middleTopLeft, middleTopLeft});
        } else if (g.isEmpty(middleTopLeft)) {
            moves.push_back(Move{currentPos, middleTopLeft});
        }
    }

    return moves;
}

unique_ptr<Moveable> MoveL::clone() const
{
    return make_unique<MoveL>(*this);
}

MoveL::MoveL(const MoveL &o) : Decorator{o} {}
