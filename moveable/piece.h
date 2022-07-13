#ifndef PIECE_H_
#define PIECE_H_
#include <vector>
#include "moveable.h"

class Position;
class Board;

class Piece : public Moveable
{
    virtual std::vector<Position> doGetDelta() override;
    virtual std::vector<Position> doGetValidMoves(Board b) override;

public:
    Piece();
    virtual ~Piece();
};
#endif