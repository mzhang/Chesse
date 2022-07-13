#include "level_1.h"
#include "../game/board.h"
#include "../data/move.h"

Move Level_One::next_move_virtual(Board &b)
{
    return Move{{0, 0}, {0, 0}};
}