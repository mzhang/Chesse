#ifndef POSITION_H_
#define POSITION_H_

#include <iostream>

struct Position
{
    int x;
    int y;
    Position(int x, int y);
    friend std::ostream &operator<<(std::ostream &os, const Position &p);
    friend std::istream &operator>>(std::istream &is, Position &p);
};

#endif
