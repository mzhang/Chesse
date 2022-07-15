#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <memory>

class Board;

class Game
{
    int boardWidth;
    int boardHeight;

    int playingPlayer; // white = 0; black = 1
    void switchPlayers();

    std::unique_ptr<Board> board;

public:
    Game();
    Game(int, int);
    ~Game();
    int play(const std::string &, const std::string &); // returns winning player

    Game(const Game &);
};

#endif