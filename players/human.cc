#include "human.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Human::Human(int playerNum) : Player{playerNum}
{
}

Move Human::doNextMove(const GameState &g)
{
    while (true) {
        Position from;
        Position to;

        cin >> from;
        cin >> to;

        Move move = Move{from, to};
        if (g.isValidMove(move)) {
            // TODO: dont return this move. Instead return the complete move we get somehow from gameState
            return move;
        }

        cout << "Invalid move, please try again" << endl;
    }
}
