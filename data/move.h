#ifndef MOVE_H_
#define MOVE_H_

#include <vector>
#include "position.h"

struct Move
{
    std::vector<Position> from;
    std::vector<Position> to;
    std::vector<Position> capturePositions;

    Move(const Position &, const Position &);
    Move(const Position &, const Position &, const Position &);
    Move(const std::vector<Position> &, const std::vector<Position> &, const std::vector<Position> & = std::vector<Position>());
    Move();
    Move(const Move &);
    ~Move();
    bool operator==(const Move &) const;
    friend std::ostream &operator<<(std::ostream &os, const Move &p);
};

#endif // MOVE_H_
