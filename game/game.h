#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <memory>
#include <vector>
#include "../players/player.h"
#include "../outputs/output.h"

class Board;

class Game
{
    int boardWidth;
    int boardHeight;

    std::vector<std::unique_ptr<Player>> players;
    int currentPlayer; // white = 0; black = 1
    void switchPlayers();

    void setupOutputs();
    std::vector<std::unique_ptr<Output>> outputs;

    std::unique_ptr<Board> board;

public:
    Game();
    Game(int, int);
    ~Game();
    int play(const std::string &, const std::string &); // returns winning player
};

#endif