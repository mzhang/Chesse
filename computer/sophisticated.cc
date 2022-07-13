#include "sophisticated.h"
#include "../game/board.h"
#include "../data/move.h"

Move Sophisticated::next_move_virtual(Board &b)
{
    return Move{{0, 0}, {0, 0}};
}