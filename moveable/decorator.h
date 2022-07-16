#ifndef DECORATOR_H_
#define DECORATOR_H_
#include "moveable.h"
#include <memory>
#include <vector>

class Board;
class Position;
enum class PieceType;
class GameState;
class Move;

class Decorator : public Moveable
{
protected:
    std::unique_ptr<Moveable> component;

public:
    explicit Decorator(std::unique_ptr<Moveable>);
    virtual ~Decorator() = 0;

    PieceType getPieceType() override;
    std::vector<Move> getValidMoves(const GameState &) override;

    Decorator(const Decorator &);
};

#endif
