#ifndef COMPUTER2_H_
#define COMPUTER2_H_

#include "player.h"

class Move;
class GameState;

class Computer2 : public Player
{
    Move doNextMove(GameState &) override;
};

#endif // COMPUTER2_H_