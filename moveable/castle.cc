#include <vector>
#include <memory>

#include "castle.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"

using namespace std;

Castle::Castle(unique_ptr<Moveable> component, vector<Position> partnerPositions) : Decorator{std::move(component)}, partnerPositions{partnerPositions} {}
Castle::Castle(const Castle &o) : Decorator{o}, partnerPositions{o.partnerPositions} {}

vector<Move> Castle::getValidMoves(const GameState &g) const
{
    vector<Move> moves = Decorator::getValidMoves(g);
    PlayerColor player = Decorator::getOwner();
    Position currentPos = getPosition();

    if (getMovedCount() != 0)
    {
        return moves;
    }

    for (auto &castlePartner : partnerPositions)
    {
        // ignore castle partners on different ranks
        if (!(g.isInBounds(castlePartner) && g.isOwner(castlePartner, player) && g.getMovedCount(castlePartner) == 0 &&
              (castlePartner != currentPos) && (currentPos.y == castlePartner.y)))
            continue;

        int direction = castlePartner.x - currentPos.x > 0 ? 1 : -1;
        Position p = currentPos;

        bool pathValid = true;
        while (++p.x < castlePartner.x)
        {
            if (!(g.isInBounds(p) && g.isEmpty(p)))
            {
                pathValid = false;
                break;
            }
        }
        if (!pathValid)
            continue;
        Position partnerPos = Position{currentPos.x + direction, currentPos.y};
        Position finalPos = Position{currentPos.x + 2 * direction, currentPos.y};
        moves.push_back(Move{vector<Position>{currentPos, castlePartner}, vector<Position>{finalPos, partnerPos}});
    }

    return moves;
}

unique_ptr<Moveable> Castle::clone() const
{
    return make_unique<Castle>(*this);
}
