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

struct PawnRules : public Decorator
{
    int enpassantRank;
    int promotionRank;

public:
    PawnRules(std::unique_ptr<Moveable>, int enpassantRank, int promotionRank);

    std::vector<Move> getValidMoves(const GameState &) const override;
    std::unique_ptr<Moveable> clone() const override;

    PawnRules(const PawnRules &);
};

#endif