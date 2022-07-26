#ifndef PAWN_RULES_H_
#define PAWN_RULES_H_

#include <vector>
#include <memory>
#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class PawnRules : public Decorator
{
    int enpassantRank;
    int promotionRank;
    bool isPromoted;
    int promotedMaxSteps;

    void promote(bool);

public:
    PawnRules(std::unique_ptr<Moveable>, int enpassantRank, int promotionRank, int promotedMaxSteps);
    PawnRules(const PawnRules &);

    std::vector<Position> getAttackedTiles(const GameState &, bool) const override;
    std::vector<Move> getValidMoves(const GameState &, bool) const override;
    std::unique_ptr<Moveable> clone() const override;

    void onMove(const Move &, const Position &, bool, int movedCountDelta = 1) override;
};

#endif