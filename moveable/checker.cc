#include <vector>
#include <memory>

#include "checker.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"
#include "../data/playerColor.h"

using namespace std;

Checker::Checker(unique_ptr<Moveable> component, int promotionRank) : Decorator{std::move(component)}, promotionRank{promotionRank}, isPromoted{false} {}

Checker::Checker(const Checker &o) : Decorator{o}, promotionRank{o.promotionRank} {}

vector<Move> Checker::getValidMoves(const GameState &g, bool checkChildren) const
{
    vector<Move> moves{};
    PlayerColor player = Decorator::getOwner();
    Position currentPos = Decorator::getPosition();

    if (checkChildren)
    {
        moves = Decorator::getValidMoves(g, true);
    }

    int forwardsDir = (player == PlayerColor::WHITE) ? 1 : -1;
    Position leftDiag = Position{currentPos.x - 1, currentPos.y + forwardsDir};
    Position rightDiag = Position{currentPos.x + 1, currentPos.y + forwardsDir};

    if (g.isInBounds(leftDiag) && g.isEmpty(leftDiag))
    {
        moves.emplace_back(Move{currentPos, leftDiag});
    }

    if (g.isInBounds(rightDiag) && g.isEmpty(rightDiag))
    {
        moves.emplace_back(Move{currentPos, rightDiag});
    }

    Position leftDiag2 = Position{currentPos.x - 1, currentPos.y + 2 * forwardsDir};
    Position rightDiag2 = Position{currentPos.x + 1, currentPos.y + 2 * forwardsDir};

    if (g.isInBounds(leftDiag) && !g.isOwner(leftDiag, player) && g.isInBounds(leftDiag2) && g.isEmpty(leftDiag2))
    {
        moves.emplace_back(Move{currentPos, leftDiag, leftDiag2});
    }

    if (g.isInBounds(rightDiag) && !g.isOwner(rightDiag, player) && g.isInBounds(rightDiag2) && g.isEmpty(rightDiag2))
    {
        moves.emplace_back(Move{currentPos, rightDiag, rightDiag2});
    }

    if (isPromoted)
    {
        int backwardsDir = (player == PlayerColor::WHITE) ? -1 : 1;
        leftDiag = Position{currentPos.x - 1, currentPos.y + backwardsDir};
        rightDiag = Position{currentPos.x + 1, currentPos.y + backwardsDir};

        if (g.isInBounds(leftDiag) && g.isEmpty(leftDiag))
        {
            moves.emplace_back(Move{currentPos, leftDiag});
        }

        if (g.isInBounds(rightDiag) && g.isEmpty(rightDiag))
        {
            moves.emplace_back(Move{currentPos, rightDiag});
        }

        leftDiag2 = Position{currentPos.x - 1, currentPos.y + 2 * backwardsDir};
        rightDiag2 = Position{currentPos.x + 1, currentPos.y + 2 * backwardsDir};

        if (g.isInBounds(leftDiag) && !g.isOwner(leftDiag, player) && g.isInBounds(leftDiag2) && g.isEmpty(leftDiag2))
        {
            moves.emplace_back(Move{currentPos, leftDiag, leftDiag2});
        }

        if (g.isInBounds(rightDiag) && !g.isOwner(rightDiag, player) && g.isInBounds(rightDiag2) && g.isEmpty(rightDiag2))
        {
            moves.emplace_back(Move{currentPos, rightDiag, rightDiag2});
        }
    }

    return moves;
}

void Checker::onMove(const Move &m, const Position &newPos, bool checkChildren, int movedCountDelta)
{
    if (!isPromoted && newPos.y == promotionRank)
    {
        isPromoted = true;
    }
    Decorator::onMove(m, newPos, checkChildren, movedCountDelta);
}

unique_ptr<Moveable> Checker::clone() const
{
    return make_unique<Checker>(*this);
}
