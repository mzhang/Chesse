#include <vector>
#include <memory>
#include "moveL.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

MoveL::MoveL(Moveable *component) : Decorator{component} {};
vector<Position> MoveL::doGetDelta(){};
vector<Position> MoveL::doGetValidMoves(Board b){};
unique_ptr<Moveable> MoveL::doClone()
{
    return make_unique<MoveL>(*this);
}

MoveL::MoveL(const MoveL &o) : Decorator{nullptr} {}
