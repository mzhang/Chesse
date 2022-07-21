#ifndef DECORATOR_H_
#define DECORATOR_H_
#include "moveable.h"
#include <memory>
#include <vector>

struct Position;
class GameState;
struct Move;
enum class PieceType;

class Decorator : public Moveable
{
    std::unique_ptr<Moveable> component;

protected:
public:
    explicit Decorator(std::unique_ptr<Moveable>);
    virtual ~Decorator() = 0;

    Position getPosition() const override;
    PieceType getPieceType() const override;
    int getOwner() const override;
    virtual std::vector<Move> getValidMoves(const GameState &) const override;

    Decorator(const Decorator &);
};

#endif
