#include <vector>
#include <memory>
#include "moveY.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

MoveY::MoveY(unique_ptr<Moveable> component) : Decorator{std::move(component)} {};

vector<Move> MoveY::getValidMoves(const GameState &g) {}

PieceType MoveY::getPieceType() {}

unique_ptr<Moveable> MoveY::clone()
{
    return make_unique<MoveY>(*this);
}

MoveY::MoveY(const MoveY &o) : Decorator{nullptr} {}
