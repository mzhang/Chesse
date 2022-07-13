#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <memory>

class Board;

class Game
{
    int boardWidth;
    int boardHeight;

    std::unique_ptr<Board> board;

public:
    Game();
    Game(int, int);
    ~Game();
    void play();

    Game(const Game &);

    friend std::istream &operator>>(std::istream &in, const Game &g);
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif