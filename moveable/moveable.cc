#include <vector>
#include <memory>
#include "moveable.h"
#include "../data/position.h"
#include "../game/board.h"

using namespace std;

vector<Position> Moveable::doGetDelta() {}
vector<Position> Moveable::doGetValidMoves(Board b) {}

Moveable::Moveable(){};

vector<Position> Moveable::getDelta(){};
vector<Position> Moveable::getValidMoves(Board b){};
bool Moveable::isInBounds(const Board b){};
void Moveable::draw(){};

Moveable::~Moveable(){};
Moveable::Moveable(const Moveable &other){};
Moveable &Moveable::operator=(const Moveable &other) { return *this; };
Moveable::Moveable(Moveable &&other){};
Moveable &Moveable::operator=(Moveable &&other) { return *this; };