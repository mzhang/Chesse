#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "../game/gameState.h"
#include "../data/move.h"

class Player
{
    virtual Move doNextMove(GameState &) = 0;
protected:
    int playerNum;
public:
    explicit Player(int);

    Move nextMove(GameState &);
};

#endif // COMPUTER_H_