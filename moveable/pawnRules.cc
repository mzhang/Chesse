#include <vector>
#include <memory>

#include "pawnRules.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"
#include "../game/board.h"

using namespace std;

PawnRules::PawnRules(unique_ptr<Moveable> component, int enpassantRank, int promotionRank) : Decorator{std::move(component)}, enpassantRank{enpassantRank}, promotionRank{promotionRank} {}
PawnRules::PawnRules(const PawnRules &o) : Decorator{o}, enpassantRank{o.enpassantRank}, promotionRank{o.promotionRank} {}

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
    if (g.isInBounds(forwards) && g.isInBounds(forwards2) && g.isEmpty(forwards) && g.isEmpty(forwards2) && Decorator::getMovedCount() == 0)
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

    Position left = Position{currentPos.x - 1, currentPos.y};
    Position right = Position{currentPos.x + 1, currentPos.y};

    if (currentPos.y + 1 == enpassantRank && g.isInBounds(left) &&
        !g.isOwner(left, player) && !g.isEmpty(left) && g.getPieceType(left) == PieceType::PAWN &&
        g.board->getPiece(left).getMovedCount() == 1)
    {
        bool lastMovedPawn = false;
        vector<Position> lastMoveTo = g.lastMove.to;
        for (int i = 0; i < (int)lastMoveTo.size(); i++)
        {
            if (lastMoveTo[i] == left && g.getPieceType(lastMoveTo[i]) == PieceType::PAWN)
            {
                lastMovedPawn = true;
                break;
            }
        }
        if (lastMovedPawn)
        {
            moves.push_back(Move{currentPos, leftDiag, left});
        }
    }

    // same for right
    if (currentPos.y + 1 == enpassantRank && g.isInBounds(right) &&
        !g.isOwner(right, player) && !g.isEmpty(right) && g.getPieceType(right) == PieceType::PAWN &&
        g.board->getPiece(right).getMovedCount() == 1)
    {
        bool lastMovedPawn = false;
        vector<Position> lastMoveTo = g.lastMove.to;
        for (int i = 0; i < (int)lastMoveTo.size(); i++)
        {
            if (lastMoveTo[i] == right && g.getPieceType(lastMoveTo[i]) == PieceType::PAWN)
            {
                lastMovedPawn = true;
                break;
            }
        }
        if (lastMovedPawn)
        {
            moves.push_back(Move{currentPos, rightDiag, right});
        }
    }

    // moves are appended, not a union. must remove duplicates
    return moves;
}

unique_ptr<Moveable> PawnRules::clone() const
{
    return make_unique<PawnRules>(*this);
}
