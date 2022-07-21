#include "move.h"
#include <vector>
#include <iostream>

using namespace std;

Move::Move() {}

Move::Move(const Position &from, const Position &to) : from{from}, to{to}, capturePositions{vector<Position>{}} {}

Move::Move(const vector<Position> &from, const vector<Position> &to, const vector<Position> &capture) : from{from}, to{to}, capturePositions{capture} {}

Move::Move(const Position &from, const Position &to, const Position &capture) : from{vector<Position>{from}}, to{vector<Position>{to}}, capturePositions{vector<Position>{capture}} {}

Move::Move(const Move &other) : from{other.from}, to{other.to}, capturePositions{other.capturePositions} {}

Move::~Move() {}

bool Move::operator==(const Move &other) const
{
    return from == other.from && to == other.to; // TODO: should probly be an exact match. Maybe add like a "isSubet" function too?
}

ostream &operator<<(ostream &os, const Move &m)
{
    for (int i = 0; i < (int)m.from.size(); i++)
    {
        os << m.from[i] << " to " << m.to[i];
        if (i < (int)m.capturePositions.size())
        {
            os << " to capture the piece at " << m.capturePositions[i];
        }
    }
    return os;
}