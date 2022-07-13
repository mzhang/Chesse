#ifndef SOPHISTICATED_H_
#define SOPHISTICATED_H_

#include "../game/board.h"
#include "../data/move.h"
#include "computer.h"

class Sophisticated : public Computer {
    Move next_move_virtual(Board &b);
};

#endif // SOPHISTICATED_H_  