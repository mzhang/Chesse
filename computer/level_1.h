#ifndef LEVEL_ONE_H_
#define LEVEL_ONE_H_

#include "../game/board.h"
#include "computer.h"

class Level_One : public Computer {
    void next_move_virtual(Board &b);
};

#endif // LEVEL_ONE_H_