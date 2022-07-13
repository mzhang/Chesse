#include <memory>
#include <iostream>
#include "game.h"
#include "board.h"

using namespace std;

Game::Game(int boardWidth, int boardHeight) : boardWidth{boardWidth}, boardHeight{boardHeight},
                                              board{make_unique<Board>(boardWidth, boardHeight)} {}

Game::~Game() {}

void Game::play()
{
    cout << "Playing Game" << endl;
}

Game::Game(const Game &o) : boardWidth{o.boardWidth}, boardHeight{o.boardHeight}, board{make_unique<Board>(*o.board)} {}

std::istream &operator>>(std::istream &in, const Game &g)
{
    cout << "Reading in Game" << endl;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Game &g)
{
    out << "Printing Game" << endl;

    return out;
}