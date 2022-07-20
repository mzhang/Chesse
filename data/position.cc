#include <iostream>
#include "position.h"

using namespace std;

Position::Position(int x, int y) : x{x}, y{y} {}

Position::Position() : x{-1}, y{-1} {} // helper constructor. This will be used to create a dummy position.

Position::~Position() {}

bool Position::operator==(const Position &other) const
{
    return x == other.x && y == other.y;
}

std::ostream &operator<<(std::ostream &os, const Position &p)
{
    if (p.x == -1 && p.y == -1)
    {
        os << "NULL POSITION";
    }
    else
    {
        char col = 'a' + p.x;
        os << col << (p.y + 1);
    }

    return os;
}

std::istream &operator>>(std::istream &is, Position &p)
{
    char col;
    int row;
    is >> col >> row;

    p.x = col - 'a'; // first column is 'a'
    p.y = row - 1;   // first row is 1

    return is;
}