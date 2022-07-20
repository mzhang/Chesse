#include "move.h"
#include <vector>
#include <iostream>

using namespace std;

Move::Move() {}

Move::Move(Position from, Position to) : from{from}, to{to} {}

Move::~Move() {}

bool Move::operator==(const Move &other) const
{
    return from == other.from && to == other.to;
}

ostream &operator<<(ostream &os, const Move &m)
{
    os << "From[0]: " << m.from[0] << "; To[0]: " << m.to[0] << ";" << endl;
    return os;
}