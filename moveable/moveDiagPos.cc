#include <vector>
#include <memory>
#include <cstdlib>

#include "moveDiagPos.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"

using namespace std;

MoveDiagPos::MoveDiagPos(unique_ptr<Moveable> component, int maxSteps) : Decorator{std::move(component)}, maxSteps{maxSteps} {}

vector<Move> MoveDiagPos::getValidMoves(const GameState &g) const
{
    vector<Move> moves = Decorator::getValidMoves(g);
    PlayerColor player = Decorator::getOwner();

    Position currentPos = getPosition();
    Position pos = currentPos;

    ++pos.x;
    --pos.y;
    while (g.isInBounds(pos) && (abs(pos.x - currentPos.x) <= maxSteps))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move{currentPos, pos});
        }
        else if (!g.isOwner(pos, player))
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
        else if (!g.isOwner(pos, player))
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
    // moves are appended, not a union. must remove duplicates
    return moves;
}

unique_ptr<Moveable> MoveDiagPos::clone() const
{
    return make_unique<MoveDiagPos>(*this);
}

MoveDiagPos::MoveDiagPos(const MoveDiagPos &o) : Decorator{o}, maxSteps{o.maxSteps} {}
