#include <vector>
#include <memory>
#include <cstdlib>

#include "moveDiagNeg.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"

using namespace std;

MoveDiagNeg::MoveDiagNeg(unique_ptr<Moveable> component, int maxSteps) : Decorator{std::move(component)}, maxSteps{maxSteps} {}

vector<Move> MoveDiagNeg::getValidMoves(const GameState &g) const
{
    vector<Move> moves = Decorator::getValidMoves(g);
    int player = Decorator::getOwner();

    Position currentPos = getPosition();
    Position pos = currentPos;

    ++pos.x;
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
        --pos.y;
    }
    // moves are appended, not a union. must remove duplicates
    return moves;
}

unique_ptr<Moveable> MoveDiagNeg::clone() const
{
    return make_unique<MoveDiagNeg>(*this);
}

MoveDiagNeg::MoveDiagNeg(const MoveDiagNeg &o) : Decorator{o}, maxSteps{o.maxSteps} {}
