#include "game.h"
#include "board.h"

using namespace std;

Game::Game() : b{new Board{width, height}} {}

Game::~Game() {}

void Game::play()
{
    cout << "Playing Game" << endl;
}

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