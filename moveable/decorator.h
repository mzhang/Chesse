#ifndef DECORATOR_H_
#define DECORATOR_H_
#include "moveable.h"
#include <memory>
#include <vector>

class Position;
class GameState;
class Move;
enum class PieceType;

class Decorator : public Moveable
{
    std::unique_ptr<Moveable> component;

protected:
public:
    explicit Decorator(std::unique_ptr<Moveable> );
    virtual ~Decorator() = 0;

    virtual Position getPosition() override;
    PieceType getPieceType() override;
    int getOwner() override;
    virtual std::vector<Move> getValidMoves(const GameState &) override;

    Decorator(const Decorator &);
};

#endif
