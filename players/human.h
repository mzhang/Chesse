#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"

struct Move;
class GameState;

class Human : public Player
{
    Move doNextMove(const GameState &) override;

public:
    explicit Human(PlayerColor);
    bool isHeadless() const override;
};

#endif // HUMAN_H_