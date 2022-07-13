#ifndef LEVEL_THREE_H_
#define LEVEL_THREE_H_

#include "../game/board.h"
#include "computer.h"

class Level_Three : public Computer {
    void next_move_virtual(Board &b);
};

#endif // LEVEL_THREE_H_