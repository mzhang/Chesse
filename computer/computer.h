#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "../game/board.h"

// Chess computer base class
class Computer {
    virtual void next_move_virtual(Board &b) = 0;
public:
    void next_move(Board &b);
};

#endif // COMPUTER_H_