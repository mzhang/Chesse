#include <memory>
#include <iostream>
#include "game.h"
#include "board.h"
#include "../data/position.h"
#include "../moveable/moveX.h"
#include "../moveable/moveY.h"

using namespace std;

Game::Game(int boardWidth, int boardHeight) : boardWidth{boardWidth}, boardHeight{boardHeight}, playingPlayer{0},
                                              board{make_unique<Board>(boardWidth, boardHeight)} {}

Game::~Game() {}

int Game::play(const string &player1, const string &player2)
{
    // TODO: set players correctly

    string cmd;
    int x, y;
    while (cin >> cmd)
    {
        if (cmd == "a") {
            cin >> x >> y;
            board->addPiece(x, y);
        }
        else if (cmd == "x") { // TODO: find some system to choose what rule to apply
            cin >> x >> y;
            board->setPiece(x, y, new MoveX{board->getPiece(x, y)});
        } else if (cmd == "y") {
            cin >> x >> y;
            board->setPiece(x, y, new MoveY{board->getPiece(x, y)});
        } else if (cmd == "v") { // print valid moves for piece
            cin >> x >> y;
            for (auto &p : board->getValidMoves(x, y))
            {
                cout << p << "; ";
            }
            cout << endl;
        } else if (cmd == "setup") {
            cout << "Custom setup not implemented" << endl; // TODO: implement
            // cin >> *board;
        } else if (cmd == "move") {
            cout << "move not implemented" << endl; // TODO: implement
            switchPlayers();
        } else if (cmd == "resign") {
            return 1-playingPlayer;
        } else {
            cout << "Invalid command" << endl;
        }
    }

    return 1-playingPlayer;
}

void Game::switchPlayers()
{
    playingPlayer = 1 - playingPlayer;
}

Game::Game(const Game &o) : boardWidth{o.boardWidth}, boardHeight{o.boardHeight}, board{make_unique<Board>(*o.board)} {}