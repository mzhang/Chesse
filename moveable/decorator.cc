#include "decorator.h"
#include "moveable.h"
#include "../game/board.h"
#include "../data/position.h"
#include <memory>
#include <iostream>

using namespace std;

vector<Position> Decorator::doGetDelta()
{
    return component->getDelta();
}
vector<Position> Decorator::doGetValidMoves(const Board &b)
{
    return component->getValidMoves(b);
}
unique_ptr<Moveable> Decorator::doClone()
{
    return component->clone();
}
void Decorator::doDraw()
{
    component->draw();
}

Decorator::Decorator(unique_ptr<Moveable> component) : component{std::move(component)} { cout << "decorator ctor" << endl; }
Decorator::~Decorator(){};

Decorator::Decorator(const Decorator &o)
{
    cout << "decorator copy ctor" << endl;
    component = o.component->clone();
}