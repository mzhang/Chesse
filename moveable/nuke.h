#ifndef NUKE_H_
#define NUKE_H_

#include <vector>
#include <memory>

#include "decorator.h"

enum class PieceType;
class GameState;
struct Move;
class Piece;
struct Moveable;

class Nuke : public Decorator
{
public:
    Nuke(std::unique_ptr<Moveable>);
    Nuke(const Nuke &);

    std::vector<Move> getValidMoves(const GameState &, bool) const override;
    std::unique_ptr<Moveable> clone() const override;
};

#endif
