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

vector<Position> Castle::getAttackedTiles(const GameState &g) const
{
    return Decorator::getAttackedTiles(g);
}

vector<Move> Castle::getValidMoves(const GameState &g, bool checkChildren) const
{
    vector<Move> moves{};
    if (checkChildren)
    {
        moves = Decorator::getValidMoves(g, true);
    }
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

        Position p = Position{currentPos.x + direction, currentPos.y};
        vector<Position> path{};

        while (g.isInBounds(p) && g.isEmpty(p) && p != castlePartner)
        {
            path.push_back(p);
            p = Position{p.x + direction, p.y};
        }
        for (const Position &p : path)
        {
            if (!g.isEmpty(p))
            {
                continue;
            }
        }
        if (g.isInCheck(player, path))
        {
            continue;
        }

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
