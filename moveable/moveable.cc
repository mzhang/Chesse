#include <vector>
#include "moveable.h"
#include "../data/position.h"
#include "../game/board.h"

using namespace std;

Moveable::Moveable(){};
Moveable::~Moveable(){};
vector<Position> Moveable::getDelta(){};
vector<Position> Moveable::getValidMoves(Board b){};
bool Moveable::isInBounds(const Board b){};
void Moveable::draw(){};
