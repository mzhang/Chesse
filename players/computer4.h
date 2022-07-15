#ifndef COMPUTER4_H_
#define COMPUTER4_H_

#include "../game/board.h"
#include "../data/move.h"
#include "player.h"

class Computer4 : public Player
{
    float evaluate(Board &b); // evaluate the board (based on piece values)
    Move doNextMove(Board &b) override;
};

#endif // COMPUTER4_H_