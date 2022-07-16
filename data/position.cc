#include <iostream>
#include "position.h"

Position::Position(int x, int y) : x{x}, y{y} {}
Position::~Position() {}

std::ostream &operator<<(std::ostream &os, const Position &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

std::istream &operator>>(std::istream &is, Position &p)
{
    is >> p.x >> p.y;
    return is;
}