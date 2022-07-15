#ifndef COMPUTER3_H_
#define COMPUTER3_H_

#include "../game/board.h"
#include "../data/move.h"
#include "player.h"

class Computer3 : public Player
{
    Move doNextMove(Board &b) override;
};

#endif // COMPUTER3_H_