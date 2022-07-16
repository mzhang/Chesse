#include "move.h"
#include <vector>

using namespace std;

Move::Move(Position from, Position to) : from{from}, to{to} {}

Move::~Move() {}