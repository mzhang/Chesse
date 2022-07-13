#include "../game/board.h"
#include "../data/move.h"
#include "level_2.h"

Move Level_Two::next_move_virtual(Board &b)
{
    return Move{{0, 0}, {0, 0}};
}