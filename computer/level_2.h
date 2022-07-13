#ifndef LEVEL_TWO_H_
#define LEVEL_TWO_H_

#include "../game/board.h"
#include "computer.h"

class Level_Two : public Computer {
    void next_move_virtual(Board &b);
};

#endif // LEVEL_TWO_H_