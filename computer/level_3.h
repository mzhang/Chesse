#ifndef LEVEL_THREE_H_
#define LEVEL_THREE_H_

#include "../game/board.h"
#include "../data/move.h"
#include "computer.h"

class Level_Three : public Computer {
    Move next_move_virtual(Board &b);
};

#endif // LEVEL_THREE_H_