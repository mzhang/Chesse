#ifndef PIECE_H_
#define PIECE_H_

#include <vector>

#include "moveable.h"
#include "../data/position.h"
#include "../data/pieceType.h"
#include "../data/playerColor.h"

class Board;
enum class PieceType;
class GameState;

class Piece : public Moveable
{
    PlayerColor playerColor;
    PieceType type;
    int movedCount;
    Position position;

protected:
public:
    Piece(int, int, PieceType, PlayerColor);
    ~Piece();

    PieceType getPieceType() const override;
    Position getPosition() const override;
    int getMovedCount() const override;
    PlayerColor getOwner() const override;
    std::vector<Move> getValidMoves(const GameState &) const override;
    std::unique_ptr<Moveable> clone() const override;

    void onMove(const Move &move, const Position &pos, bool) override;
};
#endif