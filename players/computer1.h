#ifndef COMPUTER1_H_
#define COMPUTER1_H_

#include "player.h"

class Move;
class GameState;

class Computer1 : public Player
{
    Move doNextMove(const GameState &) override;
};

#endif // COMPUTER1_H_