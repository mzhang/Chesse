#include "move.h"
#include <vector>
#include <iostream>

using namespace std;

Move::Move() {}

Move::Move(const vector<Position> &from, const vector<Position> &to, const vector<Position> &capture) : from{from}, to{to}, capturePositions{capture} {}

Move::Move(const Position &from, const Position &to, const Position &capture) : from{vector<Position>{from}}, to{vector<Position>{to}}, capturePositions{vector<Position>{capture}} {}

Move::Move(const Move &other) : from{other.from}, to{other.to}, capturePositions{other.capturePositions}
{
    cout << "Move(the class) copy ctor" << endl;
    cout << "From[0]: " << from[0] << "; To[0]: " << to[0] << ";" << endl;
}

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