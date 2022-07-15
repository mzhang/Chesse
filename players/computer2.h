#ifndef COMPUTER2_H_
#define COMPUTER2_H_

#include "../game/board.h"
#include "../data/move.h"
#include "player.h"

class Computer2 : public Player
{
    Move doNextMove(Board &b) override;
};

#endif // COMPUTER2_H_