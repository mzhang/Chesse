#include <memory>
#include <utility>
#include <iostream>

#include "game.h"
#include "gameState.h"
#include "board.h"
#include "../data/position.h"
#include "../data/pieceType.h"
#include "../moveable/moveable.h"

using namespace std;

GameState::GameState(int boardWidth, int boardHeight) : board{make_unique<Board>(boardWidth, boardHeight)}, currentPlayer{0} {}

bool GameState::isOwner(Position p, int player) const
{
    return board->getOwner(p) == player;
}

bool GameState::isEmpty(Position p) const
{
    return board->isEmpty(p);
}

bool GameState::isInBounds(Position p) const
{
    return p.x >= 0 && p.x < board->getWidth() && p.y >= 0 && p.y < board->getHeight();
}

void GameState::switchPlayers()
{
    currentPlayer = 1 - currentPlayer;
}

void GameState::setup(const Game &g) {
    string cmd;
    string pieceType;
    string colour;

    while (cin >> cmd) {
        if (cmd == "done") {
            break;
        } else if (cmd == "+") {
            cin >> pieceType;
            pair<PieceType, int> p = PieceTypeUtils::fromString(pieceType);
            Position pos;
            cin >> pos;

            board->addPiece(pos, p.first, p.second);
            g.updateOutputs();
        } else if (cmd == "-") {
            Position pos;
            cin >> pos;

            if (board->popPiece(pos)) {
                g.updateOutputs();
            }
        } else if (cmd == "=") {
            cin >> colour;
            currentPlayer = (colour == "white") ? 0 : 1;
        } else {
            cout << "Invalid command" << endl;
        }
    }
}