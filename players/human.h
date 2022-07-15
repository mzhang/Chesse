#ifndef HUMAN_H_
#define HUMAN_H_

#include "../game/board.h"
#include "../data/move.h"
#include "player.h"

class Human : public Player
{
    Move doNextMove(Board &b) override;
    public:
        Human(int);
};

#endif // HUMAN_H_