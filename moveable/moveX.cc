#include <vector>
#include <memory>
#include <iostream>
#include "moveX.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

MoveX::MoveX(Moveable *component) : Decorator{component} { cout << "X ctor" << endl; };
vector<Position> MoveX::doGetDelta(){}
vector<Position> MoveX::doGetValidMoves(Board b) 
{ 
    vector<Position> v{Position{3, 4}};
    vector<Position> componentMoves = component->doGetValidMoves(b);
    if (!componentMoves.empty())
        v.insert(v.end(), componentMoves.begin(), componentMoves.end());

    return v;
}

MoveX::MoveX(const MoveX &o) : Decorator{nullptr} {cout << "X copy ctor" << endl; } // TODO: figure out copy ctor, has to be recursive somehow....

unique_ptr<Moveable> MoveX::clone()
{
    cout << "X clone" << endl; 
    return make_unique<MoveX>(*this);
}