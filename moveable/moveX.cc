#include <vector>
#include <memory>

#include "moveX.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"

using namespace std;

MoveX::MoveX(unique_ptr<Moveable> component, int maxSteps) : Decorator{std::move(component)}, maxSteps{maxSteps} {}

int abs(int x)
{
    return x < 0 ? -x : x;
}

vector<Move> MoveX::getValidMoves(const GameState &g)
{
    vector<Move> moves = Decorator::getValidMoves(g);
    int player = Decorator::getOwner();

    Position currentPos = getPosition();
    Position pos = currentPos;

    ++pos.x;
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
    }

    pos = currentPos;
    --pos.x;
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
    }
    // moves are appended, not a union. must remove duplicates
    return moves;
}

unique_ptr<Moveable> MoveX::clone()
{
    cout << "MoveX::clone()" << endl;
    return make_unique<MoveX>(*this);
}

MoveX::MoveX(const MoveX &o) : Decorator{o}, maxSteps{o.maxSteps} {}
