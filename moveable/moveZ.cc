#include <vector>
#include <memory>
#include "moveZ.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

MoveZ::MoveZ(unique_ptr<Moveable> component) : Decorator{std::move(component)} {};

vector<Move> MoveZ::getValidMoves(const GameState &g) {}

PieceType MoveZ::getPieceType() {}

unique_ptr<Moveable> MoveZ::clone()
{
    return make_unique<MoveZ>(*this);
}

MoveZ::MoveZ(const MoveZ &o) : Decorator{nullptr} {}
