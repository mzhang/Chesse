#ifndef MOVEABLE_H_
#define MOVEABLE_H_
#include "../data/pieceType.h"
#include <vector>

class Board;
class Position;

class Moveable
{
    virtual std::vector<Position> getDelta();
    virtual std::vector<Position> getValidMoves(Board b);
    bool isInBounds(const Board b);

    PieceType name;
    virtual void draw();

public:
    Moveable();
    virtual ~Moveable() = 0;
};

#endif