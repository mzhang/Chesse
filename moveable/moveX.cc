#include <vector>
#include <memory>
#include "moveX.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

MoveX::MoveX(unique_ptr<Moveable> component) : Decorator{std::move(component)} {};

vector<Move> MoveX::getValidMoves(const GameState &g)
{
    vector<Move> moves = Decorator::getValidMoves(g);
    Position pos = getPosition();
    int player = Decorator::getOwner();

    ++pos.x;
    while (g.isInBounds(pos))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move(pos, getPosition()));
        }
        else if (!g.isOwner(pos, player))
        {
            moves.push_back(Move(pos, getPosition()));
            break;
        }
        else
        {
            break;
        }
        ++pos.x;
    }

    pos = getPosition();
    --pos.x;
    while (g.isInBounds(pos))
    {
        if (g.isEmpty(pos))
        {
            moves.push_back(Move(pos, getPosition()));
        }
        else if (!g.isOwner(pos, player))
        {
            moves.push_back(Move(pos, getPosition()));
            break;
        }
        else
        {
            break;
        }
        --pos.x;
    }
    // moves are appended, not a union. must remove duplicates.
    return moves;
}

PieceType MoveX::getPieceType()
{
    return Decorator::getPieceType();
}

unique_ptr<Moveable> MoveX::clone()
{
    return make_unique<MoveX>(*this);
}

MoveX::MoveX(const MoveX &o) : Decorator{nullptr} {}
