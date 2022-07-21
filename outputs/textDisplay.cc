#include <iostream>

#include "textDisplay.h"
#include "../game/gameState.h"
#include "../game/board.h"
#include "../data/position.h"
#include "../data/pieceType.h"
#include "../moveable/moveable.h"

using namespace std;

void TextDisplay::doUpdate(const GameState &g, const Move &)
{
    for (int y = g.board->getHeight() - 1; y >= 0; --y) { // we print in reverse order because we want to print the bottom row first
        cout << (y+1) << " ";
        for (int x = 0; x < g.board->getWidth(); ++x) {
            Position p{x, y};
            if (g.board->isEmpty(p)) {
                if (isBlackTile(p)) {
                    cout << "_";
                } else {
                    cout << " ";
                }
            } else {
                const Moveable &piece = g.board->getPiece(p);
                cout << PieceTypeUtils::toString(piece.getPieceType(), piece.getOwner());
            }
        }
        cout << endl;
    }

    cout << endl << "  ";

    char col = 'a';
    for (int x = 0; x < g.board->getWidth(); ++x) {
        cout << col;
        col++;
    }
    cout << endl;
}