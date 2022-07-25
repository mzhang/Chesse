#include <iostream>

#include "textDisplay.h"
#include "../game/gameState.h"
#include "../game/board.h"
#include "../data/position.h"
#include "../data/pieceType.h"
#include "../moveable/moveable.h"

using namespace std;

TextDisplay::TextDisplay(int boardWidth, int boardHeight) : boardWidth{boardWidth}, boardHeight{boardHeight} {}

void TextDisplay::doUpdate(const GameState &g, const Move &)
{
    for (int y = boardHeight- 1; y >= 0; --y)
    { // we print in reverse order because we want to print the bottom row first
        cout << (y + 1) << " ";
        for (int x = 0; x < boardWidth; ++x)
        {
            Position p{x, y};
            if (g.isEmpty(p))
            {
                if (isBlackTile(p))
                {
                    cout << "_";
                }
                else
                {
                    cout << " ";
                }
            }
            else
            {
                cout << PieceTypeUtils::toString(g.getPieceType(p), g.getOwner(p));
            }
        }
        cout << endl;
    }

    cout << endl
         << "  ";

    char col = 'a';
    for (int x = 0; x < boardWidth; ++x)
    {
        cout << col;
        col++;
    }
    cout << endl;
}

void TextDisplay::doDisplayValidMoves(const GameState &g, const vector<Move> &moves)
{
    cout << "You can move the piece at " << moves[0].from[0] << " in " << moves.size() << " ways:" << endl;

    for (int i = 0; i < (int)moves.size(); ++i)
    {
        cout << moves[i] << endl;
    }
}