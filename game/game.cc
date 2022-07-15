#include <memory>
#include <iostream>
#include "game.h"
#include "board.h"
#include "../data/position.h"
#include "../moveable/moveX.h"
#include "../moveable/moveY.h"
#include "../outputs/textDisplay.h"
#include "../outputs/visualizer.h"
#include "../players/human.h"

using namespace std;

Game::Game(int boardWidth, int boardHeight) : boardWidth{boardWidth}, boardHeight{boardHeight}, currentPlayer{0},
                                              board{make_unique<Board>(boardWidth, boardHeight)} {}

Game::~Game() {}

void Game::setupOutputs()
{
    outputs.push_back(make_unique<TextDisplay>());
    outputs.push_back(make_unique<Visualizer>());
}

int Game::play(const string &player1, const string &player2)
{
    // TODO: set players correctly
    // for now, we will just add two humans
    players.push_back(make_unique<Human>(0));
    players.push_back(make_unique<Human>(1));

    string cmd;
    int x, y;
    cout << "DEBUG: Player " << currentPlayer << "'s turn" << endl;
    while (cin >> cmd)
    {
        if (cmd == "a")
        {
            cin >> x >> y;
            board->addPiece(x, y);
        }
        else if (cmd == "x")
        { // TODO: find some system to choose what rule to apply
            cin >> x >> y;
            board->setPiece(x, y, new MoveX{board->getPiece(x, y)});
        }
        else if (cmd == "y")
        {
            cin >> x >> y;
            board->setPiece(x, y, new MoveY{board->getPiece(x, y)});
        }
        else if (cmd == "v")
        { // print valid moves for piece
            cin >> x >> y;
            for (auto &p : board->getValidMoves(x, y))
            {
                cout << p << "; ";
            }
            cout << endl;
        }
        else if (cmd == "setup")
        {
            cout << "Custom setup not implemented" << endl; // TODO: implement
            // cin >> *board;
        }
        else if (cmd == "move")
        {
            board->makeMove(players[currentPlayer]->nextMove(*board));
            switchPlayers();
        }
        else if (cmd == "resign")
        {
            return 1 - currentPlayer;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
        cout << "DEBUG: Player " << currentPlayer << "'s turn" << endl; 
    }

    return 1 - currentPlayer;
}

void Game::switchPlayers()
{
    currentPlayer = 1 - currentPlayer;
}