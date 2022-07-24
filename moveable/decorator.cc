#include <memory>
#include <iostream>
#include <vector>

#include "decorator.h"
#include "moveable.h"
#include "../data/move.h"
#include "../game/board.h"
#include "../data/position.h"
#include "../data/pieceType.h"

using namespace std;

Decorator::Decorator(unique_ptr<Moveable> c) : component{std::move(c)} {}

Decorator::Decorator(const Decorator &o) : component{o.component->clone()} {}

Decorator::~Decorator(){};

PieceType Decorator::getPieceType() const
{
    return component->getPieceType();
}

vector<Move> Decorator::getValidMoves(const GameState &gameState) const
{
    return component->getValidMoves(gameState);
}

Position Decorator::getPosition() const
{
    return component->getPosition();
}

int Decorator::getMovedCount() const
{
    return component->getMovedCount();
}

void Decorator::setComponent(unique_ptr<Moveable> c)
{
    component = std::move(c);
}

PlayerColor Decorator::getOwner() const
{
    return component->getOwner();
}

void Decorator::onMove(const Move &move, const Position &endPos, bool headless)
{
    component->onMove(move, endPos, headless);
}