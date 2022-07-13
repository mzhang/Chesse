#ifndef SOCHISTICATED_H_
#define SOCHISTICATED_H_

#include "../game/board.h"
#include "computer.h"

class Sophisticated : public Computer {
    void next_move_virtual(Board &b);
};

#endif // SOCHISTICATED_H_