#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <memory>
#include <vector>
#include "../players/player.h"
#include "../outputs/output.h"
#include "gameState.h"
#include "gameHistory.h"

class Board;

class Game
{
    GameState state;
    GameHistory history;

    std::vector<std::unique_ptr<Player>> players;
    void switchPlayers();

    void setupOutputs();
    std::vector<std::unique_ptr<Output>> outputs;

public:
    Game();
    Game(int, int);
    ~Game();
    int play(const std::string &, const std::string &); // returns winning player
};

#endif