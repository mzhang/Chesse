#ifndef PIECE_H_
#define PIECE_H_

#include <vector>

#include "moveable.h"
#include "../data/position.h"
#include "../data/pieceType.h"

class Board;
enum class PieceType;
class GameState;

class Piece : public Moveable
{
    int playerNum;
    PieceType type;
    bool hasMoved;
    Position position;

protected:
public:
    Piece(int, int, PieceType, int);
    ~Piece();

    PieceType getPieceType() const override;
    Position getPosition() const override;
    int getOwner() const override;
    std::vector<Move> getValidMoves(const GameState &) const override;
    std::unique_ptr<Moveable> clone() const override;
};
#endif