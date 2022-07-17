#include <memory>
#include <iostream>

#include "game.h"
#include "board.h"
#include "../outputs/textDisplay.h"
#include "../outputs/visualizer.h"
#include "../players/human.h"

using namespace std;

Game::Game(int boardWidth, int boardHeight) : state{boardWidth, boardHeight} {
    outputs.push_back(make_unique<TextDisplay>());
    outputs.push_back(make_unique<Visualizer>());
}

Game::~Game() {}

int Game::play(const string &player1, const string &player2)
{
    // TODO: set players correctly
    // for now, we will just add two humans
    players.push_back(make_unique<Human>(0));
    players.push_back(make_unique<Human>(1));

    string cmd;
    cout << "DEBUG: Player " << state.currentPlayer << "'s turn" << endl;
    while (cin >> cmd)
    {
        if (cmd == "setup")
        {
            state.setup(*this);
        }
        else if (cmd == "move")
        {
            Move move = players[state.currentPlayer]->nextMove(state);
            cout << move;

            state.board->makeMove(move);
            history.addMove(move);

            state.switchPlayers();
            updateOutputs();
        }
        else if (cmd == "resign")
        {
            state.switchPlayers();
            return state.currentPlayer;
        }
        else if (cmd == "print") 
        {
            updateOutputs();
        }
        else
        {
            cout << "Invalid command" << endl;
        }
        cout << "DEBUG: Player " << state.currentPlayer << "'s turn" << endl;
    }

    return -1;
}

void Game::updateOutputs() const
{
    for (auto &output : outputs)
    {
        output->update(state);
    }
}