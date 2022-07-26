#ifndef CHECKER_H_
#define CHECKER_H_

#include <vector>
#include <memory>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class Checker : public Decorator
{
    int promotionRank;
    bool isPromoted;

public:
    Checker(std::unique_ptr<Moveable>, int);
    Checker(const Checker &);

    std::vector<Position> getAttackedTiles(const GameState &, bool) const override;
    std::vector<Move> getValidMoves(const GameState &, bool) const override;
    std::unique_ptr<Moveable> clone() const override;
    void onMove(const Move &, const Position &, bool, int) override;
};

#endif
