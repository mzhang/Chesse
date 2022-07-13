#ifndef MOVEABLES_H_
#define MOVEABLES_H_

#include <vector>

class Board;
class Position;

class Moveable
{
    enum class Name
    {
        KING,
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN
    };

    virtual std::vector<Position> getDelta();
    virtual std::vector<Position> getValidMoves(Board b);
    bool isInBounds(const Board b);

    Name name;
    virtual void draw();

public:
    Moveables();
    virtual ~Moveables() = 0;
};

#endif