#include <vector>
#include "moveable.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

Piece::Piece() {}
Piece::~Piece() {}
vector<Position> Piece::doGetDelta() {}
vector<Position> Piece::doGetValidMoves(Board b) {}
