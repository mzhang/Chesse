#ifndef DECORATOR_H_
#define DECORATOR_H_
#include "moveable.h"
#include <memory>
#include <vector>

struct Position;
class GameState;
struct Move;
enum class PieceType;
enum class PlayerColor;

class Decorator : public Moveable
{
    std::unique_ptr<Moveable> component;

protected:
    void setComponent(std::unique_ptr<Moveable>);

public:
    explicit Decorator(std::unique_ptr<Moveable>);
    Decorator(const Decorator &);
    virtual ~Decorator() = 0;

    Position getPosition() const override;
    PieceType getPieceType() const override;
    PlayerColor getOwner() const override;
    virtual std::vector<Move> getValidMoves(const GameState &, bool) const override;
    virtual std::vector<Position> getAttackedTiles(const GameState &, bool) const override;

    int getMovedCount() const;
    virtual void onMove(const Move &, const Position &, bool, int movedCountDelta = 1) override;
};

#endif
