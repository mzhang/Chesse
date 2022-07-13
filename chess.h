#ifndef CHESS_H_
#define CHESS_H_

#include <memory>

class Game;

class Chess
{
    std::unique_ptr<Game> g;
public:
    Chess();
    ~Chess();
    void start();
};

#endif
