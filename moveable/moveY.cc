#include <vector>
#include <memory>
#include <iostream>
#include "moveY.h"
#include "../data/position.h"
#include "../game/board.h"
#include "piece.h"

using namespace std;

MoveY::MoveY(unique_ptr<Moveable> component) : Decorator{std::move(component)} { cout << "Y ctor" << endl; }
vector<Position> MoveY::doGetDelta() {}
vector<Position> MoveY::doGetValidMoves(const Board &b)
{
    vector<Position> v{Position{1, 2}};
    vector<Position> componentMoves = component->getValidMoves(b);
    if (!componentMoves.empty())
        v.insert(v.end(), componentMoves.begin(), componentMoves.end());

    return v;
}
unique_ptr<Moveable> MoveY::doClone()
{
    cout << "Y clone" << endl;
    return make_unique<MoveY>(*this);
}

MoveY::MoveY(const MoveY &o) : Decorator{nullptr} { cout << "Y copy ctor" << endl; }
