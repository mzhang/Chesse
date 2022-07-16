#include <vector>
#include <memory>
#include "moveX.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

MoveX::MoveX(unique_ptr<Moveable> component) : Decorator{std::move(component)} {};

vector<Move> MoveX::getValidMoves(const GameState &g)
{
    vector<Move> moves = component->getValidMoves(g);
}

PieceType MoveX::getPieceType()
{
    return component->getPieceType();
}

unique_ptr<Moveable> MoveX::clone()
{
    return make_unique<MoveX>(*this);
}

MoveX::MoveX(const MoveX &o) : Decorator{nullptr} {}
