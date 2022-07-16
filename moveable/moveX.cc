#include <vector>
#include <memory>
#include <iostream>
#include "moveX.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

MoveX::MoveX(unique_ptr<Moveable> component) : Decorator{std::move(component)} { cout << "X ctor" << endl; }
vector<Position> MoveX::doGetDelta(){}
vector<Position> MoveX::doGetValidMoves(const Board &b) 
{ 
    vector<Position> v{Position{3, 4}};
    vector<Position> componentMoves = component->getValidMoves(b);
    if (!componentMoves.empty())
        v.insert(v.end(), componentMoves.begin(), componentMoves.end());

    return v;
}
unique_ptr<Moveable> MoveX::doClone()
{
    cout << "X clone" << endl;
    return make_unique<MoveX>(*this);
}

MoveX::MoveX(const MoveX &o) : Decorator{nullptr} { cout << "X copy ctor" << endl; } // TODO: figure out copy ctor, has to be recursive somehow....
