#ifndef CANNIBAL_H_
#define CANNIBAL_H_

#include <vector>
#include <memory>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class Cannibal : public Decorator
{
public:
    explicit Cannibal(std::unique_ptr<Moveable>);
    Cannibal(const Cannibal &);

    std::vector<Move> getValidMoves(const GameState &, bool) const override;
    std::unique_ptr<Moveable> clone() const override;
    void onMove(const Move &, const Position &, bool) override;
};

#endif