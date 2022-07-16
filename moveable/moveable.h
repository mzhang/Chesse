#ifndef MOVEABLE_H_
#define MOVEABLE_H_
#include "../data/pieceType.h"
#include <vector>
#include <memory>

class Board;
class Position;
enum class PieceType;
class Move;
class GameState;

class Moveable
{
protected:
public:
    Moveable();
    virtual Position getPosition() = 0;
    virtual PieceType getPieceType() = 0;
    virtual int getOwner() = 0;
    virtual std::vector<Move> getValidMoves(const GameState &) = 0;
    virtual std::unique_ptr<Moveable> clone() = 0;

    virtual ~Moveable() = 0;
};

#endif