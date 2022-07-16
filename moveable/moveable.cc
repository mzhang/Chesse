#include <vector>
#include <memory>
#include "moveable.h"
#include "../data/position.h"
#include "../game/board.h"

using namespace std;

vector<Position> Moveable::getDelta() {
    return doGetDelta();
}
vector<Position> Moveable::getValidMoves(const Board& b) {
    return doGetValidMoves(b);
}

unique_ptr<Moveable> Moveable::clone() {
    return doClone();
}

void Moveable::draw() {
    doDraw();
}

Moveable::Moveable(){};

// vector<Position> Moveable::getDelta(){};
// vector<Position> Moveable::getValidMoves(const Board& b){};
bool Moveable::isInBounds(const Board b){};

Moveable::~Moveable(){};
Moveable::Moveable(const Moveable &other){};
Moveable &Moveable::operator=(const Moveable &other) { return *this; };
Moveable::Moveable(Moveable &&other){};
Moveable &Moveable::operator=(Moveable &&other) { return *this; };