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

    while (cin >> from >> to)
    {
        // TODO: if we are moving a pawn to last rank, require extra char input for promotion
        Move move = Move{from, to};
        vector<Move> validMoves = g.getValidMoves(from);

        for (Move m : validMoves)
        {
            if (move.isSubset(m))
            {
                return m;
            }
        }

        cout << "Invalid move, please try again" << endl;
    }
}
