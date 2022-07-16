#include "decorator.h"
#include "moveable.h"
#include "../data/move.h"
#include "../game/board.h"
#include "../data/position.h"
#include "../data/pieceType.h"
#include <memory>
#include <iostream>
#include <vector>

using namespace std;

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

Decorator::Decorator(unique_ptr<Moveable> component) : component{std::move(component)} { cout << "decorator ctor" << endl; }
Decorator::~Decorator(){};

Decorator::Decorator(const Decorator &o)
{
    cout << "decorator copy ctor" << endl;
    component = o.component->clone();
}