#include "human.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Human::Human(int playerNum) : Player{playerNum}
{
}

Move Human::doNextMove(const GameState &g)
{
    Position from;
    Position to;

    while (cin >> from >> to) {
        // TODO: validate positions are inside bounds
        // TODO: if we are moving a pawn to last rank, require extra char input for promotion
        Move move = Move{from, to};

        if (g.isOwner(from, playerNum) && g.isValidMove(move)) {
            // TODO: dont return this move. Instead return the complete move we get somehow from gameState
            return move;
        }

        cout << "Invalid move, please try again" << endl;
    }
}
