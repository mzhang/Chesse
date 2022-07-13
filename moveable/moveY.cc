#include <vector>
#include <memory>
#include "moveY.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

MoveY::MoveY(Moveable *component) : Decorator{component} {};
vector<Position> MoveY::doGetDelta(){};
vector<Position> MoveY::doGetValidMoves(Board b){};