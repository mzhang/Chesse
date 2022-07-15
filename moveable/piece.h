#ifndef PIECE_H_
#define PIECE_H_
#include <vector>
#include "moveable.h"

class Position;
class Board;

class Piece : public Moveable
{
public:
    Piece();
    virtual ~Piece();
    Piece(const Piece &);

    std::vector<Position> doGetDelta() override;
    std::vector<Position> doGetValidMoves(Board b) override;
    std::unique_ptr<Moveable> doClone() override;
    void doDraw() override;
};
#endif