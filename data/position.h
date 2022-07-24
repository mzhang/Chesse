#ifndef POSITION_H_
#define POSITION_H_

#include <iostream>

struct Position
{
    int x;
    int y;
    Position();
    Position(int x, int y);
    ~Position();
    bool operator==(const Position &) const;
    bool operator!=(const Position &) const;
    friend std::ostream &operator<<(std::ostream &os, const Position &p);
    friend std::istream &operator>>(std::istream &is, Position &p);
};

#endif
