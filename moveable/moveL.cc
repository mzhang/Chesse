#include <vector>
#include <memory>
#include "moveL.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

MoveL::MoveL(unique_ptr<Moveable> component) : Decorator{std::move(component)} {};

vector<Move> MoveL::getValidMoves(const GameState &g) {}

PieceType MoveL::getPieceType() {}

unique_ptr<Moveable> MoveL::clone()
{
    return make_unique<MoveL>(*this);
}

MoveL::MoveL(const MoveL &o) : Decorator{nullptr} {}
