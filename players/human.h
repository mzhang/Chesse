#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"

class Move;
class GameState;

class Human : public Player
{
    Move doNextMove(GameState &) override;
    public:
        Human(int);
};

#endif // HUMAN_H_