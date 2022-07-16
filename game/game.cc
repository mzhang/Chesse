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

Game::Game(int boardWidth, int boardHeight) : state{boardWidth, boardHeight} {}

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
    cout << "DEBUG: Player " << state.currentPlayer << "'s turn" << endl;
    while (cin >> cmd)
    {
        if (cmd == "setup")
        {
            cout << "Custom setup not implemented" << endl; // TODO: implement
            // cin >> *board;
        }
        else if (cmd == "move")
        {
            Move move = players[state.currentPlayer]->nextMove(state);
            // state.board->makeMove(move);
            // history.addMove(move);
            switchPlayers();
        }
        else if (cmd == "resign")
        {
            switchPlayers();
            return state.currentPlayer;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
        cout << "DEBUG: Player " << state.currentPlayer << "'s turn" << endl;
    }

    switchPlayers();
    return state.currentPlayer;
}

void Game::switchPlayers()
{
    state.currentPlayer = 1 - state.currentPlayer;
}