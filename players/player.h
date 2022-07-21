#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "../data/playerColor.h"

class GameState;
struct Move;

class Player
{
    virtual Move doNextMove(const GameState &) = 0;

protected:
    PlayerColor playerColor;

public:
    explicit Player(PlayerColor);

    Move nextMove(const GameState &);
};

#endif // COMPUTER_H_