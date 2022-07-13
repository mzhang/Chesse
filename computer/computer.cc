#include "computer.h"
#include "../game/board.h"
#include "../data/move.h"

Move Computer::next_move(Board &b)
{
    next_move_virtual(b);
}