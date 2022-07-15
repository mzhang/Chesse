#include "human.h"
#include "../game/board.h"
#include "../data/move.h"

using namespace std;

Human::Human(int playerNum) : Player{playerNum}
{
}

Move Human::doNextMove(Board &b)
{
    // TODO: read in move and check if valid. If it is, return it.
    cout << "Reading in move unimplemented, doing nothing" << endl;
}