#include <vector>
#include <memory>
#include <algorithm>
#include <utility>

#include "pawnRules.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"
#include "../game/board.h"
#include "pieceFactory.h"

using namespace std;

PawnRules::PawnRules(unique_ptr<Moveable> component, int enpassantRank, int promotionRank, int promotedMaxSteps) : Decorator{std::move(component)}, enpassantRank{enpassantRank}, promotionRank{promotionRank}, isPromoted{false}, promotedMaxSteps{promotedMaxSteps} {}
PawnRules::PawnRules(const PawnRules &o) : Decorator{o}, enpassantRank{o.enpassantRank}, promotionRank{o.promotionRank}, isPromoted{o.isPromoted}, promotedMaxSteps{o.promotedMaxSteps} {}

vector<Position> PawnRules::getAttackedTiles(const GameState &g, bool) const
{
    Position currentPos = Decorator::getPosition();
    vector<Position> tiles = Decorator::getAttackedTiles(g, true);
    tiles.emplace_back(Position{currentPos.x - 1, currentPos.y + 1});
    tiles.emplace_back(Position{currentPos.x + 1, currentPos.y + 1});
    return tiles;
}

vector<Move> PawnRules::getValidMoves(const GameState &g, bool checkChildren) const
{
    vector<Move> moves{};
    if (checkChildren)
    {
        moves = Decorator::getValidMoves(g, true);
    }
    PlayerColor player = Decorator::getOwner();
    Position currentPos = Decorator::getPosition();

    if (isPromoted)
    {
        return moves;
    }

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
        g.getMovedCount(right) == 1)
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
        g.getMovedCount(right) == 1)
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

void PawnRules::onMove(const Move &m, const Position &pos, bool headless, int movedCountDelta)
{
    if (pos.y == promotionRank && !isPromoted)
    {
        isPromoted = true;
        promote(headless);
    }
    Decorator::onMove(m, pos, headless, movedCountDelta);
}

void PawnRules::promote(bool headless) 
{
    PlayerColor player = Decorator::getOwner();
    Position currentPos = Decorator::getPosition();

    if (headless)
    {
        Decorator::setComponent(PieceFactory::createPiece(currentPos, PieceType::QUEEN, player, promotedMaxSteps, promotedMaxSteps));
        return;
    }

    vector<PieceType> validPromotions = {PieceType::QUEEN, PieceType::ROOK, PieceType::BISHOP, PieceType::KNIGHT};

    cout << "Choose a promotion for the piece at " << currentPos << ":" << endl;
    for (int i = 0; i < (int)validPromotions.size(); i++)
    {
        cout << PieceTypeUtils::toString(validPromotions[i], player) << " ";
    }
    cout << endl;

    string pieceType;
    cin >> pieceType;

    pair<PieceType, PlayerColor> promotion = PieceTypeUtils::fromString(pieceType);

    while (find(validPromotions.begin(), validPromotions.end(), promotion.first) == validPromotions.end() || promotion.second != player)
    {
        cout << "Invalid piece type. Try again." << endl;
        cin >> pieceType;
        promotion = PieceTypeUtils::fromString(pieceType);
    }

    Decorator::setComponent(PieceFactory::createPiece(currentPos, promotion.first, player, promotedMaxSteps, promotedMaxSteps));
}

unique_ptr<Moveable> PawnRules::clone() const
{
    return make_unique<PawnRules>(*this);
}
