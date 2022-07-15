#include "player.h"
#include "../game/board.h"
#include "../data/move.h"

Player::Player(int playerNum) : playerNum(playerNum)
{
}

Move Player::nextMove(Board &b)
{
    doNextMove(b);
}