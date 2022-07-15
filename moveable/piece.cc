#include <vector>
#include "moveable.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

Piece::Piece() {}
Piece::~Piece() {}

vector<Position> Piece::doGetDelta() {}
vector<Position> Piece::doGetValidMoves(Board b) { return vector<Position>{Position{0, 0}}; }
unique_ptr<Moveable> Piece::doClone()
{
    return make_unique<Piece>(*this);
}
void Piece::doDraw() {}

Piece::Piece(const Piece &o) {}
