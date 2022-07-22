#ifndef MOVE_H_
#define MOVE_H_

#include <vector>
#include <memory>
#include "position.h"

#include "../moveable/moveable.h"

struct Move
{
    std::vector<Position> from;
    std::vector<Position> to;
    std::vector<Position> capturePositions;
    std::vector<std::unique_ptr<Moveable>> piecesCaptured;

    Move(const Position &, const Position &);
    Move(const Position &, const Position &, const Position &);
    Move(const std::vector<Position> &, const std::vector<Position> &, const std::vector<Position> & = std::vector<Position>());
    Move();
    Move(Move &&);
    Move(const Move &);
    Move &operator=(const Move &);
    Move &operator=(Move &&);
    void swap(Move &);
    ~Move();
    bool isSubset(const Move &) const;
    bool operator==(const Move &) const;
    friend std::ostream &operator<<(std::ostream &os, const Move &p);
};

#endif // MOVE_H_
