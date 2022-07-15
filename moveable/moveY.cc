#include <vector>
#include <memory>
#include <iostream>
#include "moveY.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

MoveY::MoveY(Moveable *component) : Decorator{component} { cout << "Y ctor" << endl; };
vector<Position> MoveY::doGetDelta() {}
vector<Position> MoveY::doGetValidMoves(Board b) 
{ 
    vector<Position> v{Position{1, 2}};
    vector<Position> componentMoves = component->doGetValidMoves(b);
    if (!componentMoves.empty())
        v.insert(v.end(), componentMoves.begin(), componentMoves.end());

    return v;
}

MoveY::MoveY(const MoveY &o) : Decorator{nullptr} { cout << "Y copy ctor" << endl; }

unique_ptr<Moveable> MoveY::clone()
{
    cout << "Y clone" << endl;
    return make_unique<MoveY>(*this);
}