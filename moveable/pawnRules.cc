#include <vector>
#include <memory>

#include "pawnRules.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"

using namespace std;

PawnRules::PawnRules(unique_ptr<Moveable> component) : Decorator{std::move(component)} {}
PawnRules::PawnRules(const PawnRules &o) : Decorator{o} {}

vector<Move> PawnRules::getValidMoves(const GameState &g) const
{
    vector<Move> moves = Decorator::getValidMoves(g);
    PlayerColor player = Decorator::getOwner();
    Position currentPos = Decorator::getPosition();

    int forwardsDir = (player == PlayerColor::WHITE) ? 1 : -1;
    Position forwards = Position{currentPos.x, currentPos.y + forwardsDir};
    Position forwards2 = Position{currentPos.x, currentPos.y + 2 * forwardsDir};
    if (g.isInBounds(forwards) && g.isEmpty(forwards))
    {
        moves.push_back(Move{currentPos, forwards});
    }
    if (g.isInBounds(forwards) && g.isInBounds(forwards2) && g.isEmpty(forwards) && g.isEmpty(forwards2) && !Decorator::getHasMoved())
    {
        moves.push_back(Move{currentPos, forwards2});
    }

    Position leftDiag = Position{currentPos.x - 1, currentPos.y + forwardsDir};
    Position rightDiag = Position{currentPos.x + 1, currentPos.y + forwardsDir};
    if (g.isInBounds(leftDiag) && !g.isOwner(leftDiag, player) && !g.isEmpty(leftDiag))
    {
        moves.push_back(Move{currentPos, leftDiag, leftDiag});
    }
    if (g.isInBounds(rightDiag) && !g.isOwner(rightDiag, player) && !g.isEmpty(rightDiag))
    {
        moves.push_back(Move{currentPos, rightDiag, rightDiag});
    }

    // moves are appended, not a union. must remove duplicates
    return moves;
}

unique_ptr<Moveable> PawnRules::clone() const
{
    return make_unique<PawnRules>(*this);
}
