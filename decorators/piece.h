#ifndef MOVEABLES_H_
#define MOVEABLES_H_
#include <vector>
#include "moveables.h"

class Position;
class Board;

class Piece : public Moveables
{
    virtual std::vector<Position> getDelta();
    virtual std::vector<Position> getValidMoves(Board b);

public:
    Piece();
    virtual ~Piece();
};
#endif