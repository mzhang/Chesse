#include <vector>
#include <memory>
#include "moveX.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

MoveX::MoveX(Moveable *component) : Decorator{component} {};
vector<Position> MoveX::doGetDelta(){};
vector<Position> MoveX::doGetValidMoves(Board b){};