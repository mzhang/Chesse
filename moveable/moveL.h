#ifndef MOVE_L_H_
#define MOVE_L_H_

#include <vector>
#include <memory>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class MoveL : public Decorator
{
public:
    explicit MoveL(std::unique_ptr<Moveable>);

    std::vector<Move> getValidMoves(const GameState &, bool) const override;
    std::unique_ptr<Moveable> clone() const override;

    MoveL(const MoveL &);
};

#endif
