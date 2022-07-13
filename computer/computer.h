#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "../game/board.h"
#include "../data/move.h"

// Chess computer base class
class Computer
{
    virtual Move next_move_virtual(Board &b) = 0;

public:
    Move next_move(Board &b);
};

#endif // COMPUTER_H_