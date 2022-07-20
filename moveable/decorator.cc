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

Decorator::Decorator(unique_ptr<Moveable> c) : component{std::move(c)}
{
    cout << "decorator unique_ptr ctor ";
    cout << component->getPosition() << endl;
}

Decorator::~Decorator(){};

PieceType Decorator::getPieceType()
{
    return component->getPieceType();
}

vector<Move> Decorator::getValidMoves(const GameState &gameState)
{
    return component->getValidMoves(gameState);
}

Position Decorator::getPosition()
{
    return component->getPosition();
}

int Decorator::getOwner()
{
    return component->getOwner();
}

Decorator::Decorator(const Decorator &o)
{
    component = o.component->clone();
}