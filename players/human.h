#ifndef HUMAN_H_
#define HUMAN_H_

#include "../game/gameState.h"
#include "../data/move.h"
#include "player.h"

class Human : public Player
{
    Move doNextMove(GameState &) override;
    public:
        Human(int);
};

#endif // HUMAN_H_