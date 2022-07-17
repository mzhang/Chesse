#ifndef COMPUTER3_H_
#define COMPUTER3_H_

#include "player.h"

class Move;
class GameState;

class Computer3 : public Player
{
    Move doNextMove(GameState &) override;
};

#endif // COMPUTER3_H_