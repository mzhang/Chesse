#include <vector>
#include "moveable.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

Piece::Piece() {}
Piece::~Piece() {}
vector<Position> Piece::getDelta() {}
vector<Position> Piece::getValidMoves(Board b) {}
