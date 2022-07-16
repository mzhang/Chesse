#include <vector>
#include <memory>
#include "moveZ.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

MoveZ::MoveZ(unique_ptr<Moveable> component) : Decorator{std::move(component)} {}
vector<Position> MoveZ::doGetDelta(){};
vector<Position> MoveZ::doGetValidMoves(Board b){};

MoveZ::MoveZ(const MoveZ &o) : Decorator{nullptr} {}

unique_ptr<Moveable> MoveZ::clone()
{
    return make_unique<MoveZ>(*this);
}