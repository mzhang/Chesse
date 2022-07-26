#include <vector>
#include <memory>

#include "golem.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"
#include "../data/playerColor.h"

using namespace std;

Golem::Golem(unique_ptr<Moveable> component, int maxMoves) : Decorator{std::move(component)}, maxMoves{maxMoves}, isBroken{false} {}

Golem::Golem(const Golem &o) : Decorator{o}, maxMoves{o.maxMoves}, isBroken{o.isBroken} {}

vector<Move> Golem::getValidMoves(const GameState &g, bool checkChildren) const
{
    vector<Move> moves{};
    if (isBroken)
    {
        return moves;
    }
    if (checkChildren)
    {
        moves = Decorator::getValidMoves(g, true);
    }
    PlayerColor playerColor = Decorator::getOwner();
    Position currentPos = getPosition();
    Position pos = currentPos;
    int maxSteps = getMovedCount() + 1;

    ++pos.x;
    while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, playerColor))
        {
            moves.push_back(Move{currentPos, pos, pos});
            break;
        }
        else
        {
            break;
        }
        ++pos.x;
    }

    pos = currentPos;
    --pos.x;
    while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, playerColor))
        {
            moves.push_back(Move{currentPos, pos, pos});
            break;
        }
        else
        {
            break;
        }
        --pos.x;
    }
    pos = currentPos;

    ++pos.y;
    while (g.isInBounds(pos) && (abs(pos.y - currentPos.y) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, playerColor))
        {
            moves.push_back(Move{currentPos, pos, pos});
            break;
        }
        else
        {
            break;
        }
        ++pos.y;
    }

    pos = currentPos;
    --pos.y;
    while (g.isInBounds(pos) && (abs(pos.y - currentPos.y) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, playerColor))
        {
            moves.push_back(Move{currentPos, pos, pos});
            break;
        }
        else
        {
            break;
        }
        --pos.y;
    }
    pos = currentPos;

    ++pos.x;
    --pos.y;
    while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, playerColor))
        {
            moves.push_back(Move{currentPos, pos, pos});
            break;
        }
        else
        {
            break;
        }
        ++pos.x;
        --pos.y;
    }

    pos = currentPos;
    --pos.x;
    ++pos.y;
    while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, playerColor))
        {
            moves.push_back(Move{currentPos, pos, pos});
            break;
        }
        else
        {
            break;
        }
        --pos.x;
        ++pos.y;
    }
    pos = currentPos;

    ++pos.x;
    ++pos.y;
    while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, playerColor))
        {
            moves.push_back(Move{currentPos, pos, pos});
            break;
        }
        else
        {
            break;
        }
        ++pos.x;
        ++pos.y;
    }

    pos = currentPos;
    --pos.x;
    --pos.y;
    while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, playerColor))
        {
            moves.push_back(Move{currentPos, pos, pos});
            break;
        }
        else
        {
            break;
        }
        --pos.x;
        --pos.y;
    }

    // moves are appended, not a union. must remove duplicates
    return moves;
}

void Golem::onMove(const Move &move, const Position &to, bool headless, int movedCountDelta)
{
    if (!isBroken && getMovedCount() >= maxMoves)
    {
        isBroken = true;
    }
    Decorator::onMove(move, to, headless, movedCountDelta);
}

unique_ptr<Moveable> Golem::clone() const
{
    return make_unique<Golem>(*this);
}
