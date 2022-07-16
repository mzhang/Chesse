#ifndef MOVE_H_
#define MOVE_H_

#include <vector>
#include "position.h"

struct Move
{
    std::vector<Position> from;
    std::vector<Position> to;
    std::vector<Position> capturePositions;
    Move(Position, Position);
    ~Move();
};

#endif // MOVE_H_
