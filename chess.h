#ifndef CHESS_H_
#define CHESS_H_

#include <memory>
#include <vector>

class Game;

class Chess
{
    const int playerCount = 2;
    std::vector<int> playerScores;

    const int boardWidth = 8;
    const int boardHeight = 8;
    std::unique_ptr<Game> g;

public:
    Chess();
    ~Chess();
    void start();
};

#endif
