#ifndef MOVEABLE_H_
#define MOVEABLE_H_
#include "../data/pieceType.h"
#include <vector>
#include <memory>

class Board;
class Position;

class Moveable
{
    virtual std::vector<Position> doGetDelta() = 0;
    virtual std::vector<Position> doGetValidMoves(const Board &b) = 0;
    virtual std::unique_ptr<Moveable> doClone() = 0;
    virtual void doDraw() = 0;

    bool isInBounds(const Board b);

    PieceType name;

public:
    Moveable();
    std::vector<Position> getDelta();
    std::vector<Position> getValidMoves(const Board &b);
    std::unique_ptr<Moveable> clone();
    void draw();

    virtual ~Moveable() = 0;
    Moveable(const Moveable &other);
    Moveable &operator=(const Moveable &other);
    Moveable(Moveable &&other);
    Moveable &operator=(Moveable &&other);
};

#endif