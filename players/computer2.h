#ifndef COMPUTER2_H_
#define COMPUTER2_H_

#include "player.h"

struct Move;
class GameState;

class Computer2 : public Player
{
    Move doNextMove(const GameState &) override;
};

#endif // COMPUTER2_H_