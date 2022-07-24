#ifndef MOVEABLE_H_
#define MOVEABLE_H_

#include <vector>
#include <memory>

class Board;
struct Position;
enum class PieceType;
struct Move;
class GameState;
enum class PlayerColor;

struct Moveable
{
protected:
public:
    Moveable();
    virtual Position getPosition() const = 0;
    virtual PieceType getPieceType() const = 0;
    virtual PlayerColor getOwner() const = 0;
    virtual int getMovedCount() const = 0;
    virtual std::vector<Move> getValidMoves(const GameState &, bool = true) const = 0;
    virtual std::vector<Position> getAttackedTiles(const GameState &) const = 0;
    virtual std::unique_ptr<Moveable> clone() const = 0;
    virtual void onMove(const Move &, const Position &, bool) = 0;
    virtual ~Moveable() = 0;
};

#endif