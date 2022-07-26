#include <vector>
#include <memory>

#include "cannibal.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"

using namespace std;

Cannibal::Cannibal(unique_ptr<Moveable> component) : Decorator{std::move(component)} {}

Cannibal::Cannibal(const Cannibal &o) : Decorator{o} {}

vector<Move> Cannibal::getValidMoves(const GameState &g, bool checkChildren) const
{
    vector<Move> moves{};
    if (checkChildren)
    {
        moves = Decorator::getValidMoves(g, true);
    }
    Position currentPos = Decorator::getPosition();
    // add all tiles in a 3x3 area
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            Position pos = {currentPos.x + i, currentPos.y + j};
            if (g.isInBounds(pos) && pos != currentPos)
            {
                validMoves.push_back(Move{currentPos, pos});
            }
        }
    }

    return validMoves;
}

void Cannibal::onMove(const Move &move, const Position &to, bool headless)
{
    // cannibal gets the moveset of the pieces it takes, even if it's your own piece!
    // TODO: implement onMove; requires CompleteMoves
    Decorator::onMove(move, to, headless);
}

unique_ptr<Moveable> Cannibal::clone() const
{
    return make_unique<Cannibal>(*this);
}
