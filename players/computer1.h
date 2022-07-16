#ifndef COMPUTER1_H_
#define COMPUTER1_H_

#include "../game/gameState.h"
#include "../data/move.h"
#include "player.h"

class Computer1 : public Player
{
    Move doNextMove(GameState &) override;
};

#endif // COMPUTER1_H_