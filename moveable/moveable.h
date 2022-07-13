#ifndef MOVEABLE_H_
#define MOVEABLE_H_
#include "../data/pieceType.h"
#include <vector>
#include <memory>

class Board;
class Position;

class Moveable
{
    virtual std::vector<Position> doGetDelta();
    virtual std::vector<Position> doGetValidMoves(Board b);
    bool isInBounds(const Board b);

    PieceType name;
    virtual void draw();

public:
    Moveable();
    std::vector<Position> getDelta();
    std::vector<Position> getValidMoves(Board b);

    virtual std::unique_ptr<Moveable> clone() = 0;

    virtual ~Moveable() = 0;
    Moveable(const Moveable &other);
    Moveable &operator=(const Moveable &other);
    Moveable(Moveable &&other);
    Moveable &operator=(Moveable &&other);
};

#endif