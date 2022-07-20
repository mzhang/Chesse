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

MoveX::MoveX(unique_ptr<Moveable> component, int maxSteps) : Decorator{std::move(component)}, maxSteps{maxSteps}
{
    cout << "MoveX unique_ptr ctor" << endl;
};

vector<Move> MoveX::getValidMoves(const GameState &g)
{
    vector<Move> moves = Decorator::getValidMoves(g);
    int player = Decorator::getOwner();

    Position currentPos = getPosition();
    Position pos = currentPos;

    ++pos.y;
    while (g.isInBounds(pos) && pos.y - currentPos.y <= maxSteps)
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
        ++pos.y;
    }

    pos = currentPos;
    --pos.y;
    while (g.isInBounds(pos) && pos.y - currentPos.y <= maxSteps)
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
        --pos.y;
    }
    // moves are appended, not a union. must remove duplicates
    return moves;
}

unique_ptr<Moveable> MoveX::clone()
{
    return make_unique<MoveX>(*this);
}

MoveX::MoveX(const MoveX &o) : Decorator{nullptr} {}
