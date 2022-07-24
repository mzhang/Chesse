#include "human.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Human::Human(PlayerColor color) : Player{color}
{
}

bool Human::isHeadless() const
{
    return false;
}

Move Human::doNextMove(const GameState &g)
{
    Position from;
    Position to;

    while (cin >> from >> to)
    {
        // Validate that from and to are valid positions using g.isInBounds()
        if (!(g.isInBounds(from) && g.isInBounds(to)))
        {
            cout << "Invalid positions, please try again" << endl;
            continue;
        }

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
