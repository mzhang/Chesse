#ifndef MOVE_H_
#define MOVE_H_

#include <vector>
#include "position.h"

struct Move {
    Position from;
    Position to;
    std::vector<Position> capturePositions;
    Move(Position, Position);
};

#endif // MOVE_H_
