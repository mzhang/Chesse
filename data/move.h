#ifndef MOVE_H_
#define MOVE_H_

#include "position.h"

struct Move {
    Position from;
    Position to;
    Move(Position, Position);
};

#endif // MOVE_H_
