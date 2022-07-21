#include <memory>
#include <iostream>

#include "game.h"
#include "board.h"
#include "../outputs/textDisplay.h"
#include "../outputs/visualizer.h"
#include "../players/human.h"
#include "../players/computer1.h"
#include "../players/computer2.h"
#include "../players/computer3.h"
#include "../players/computer4.h"

using namespace std;

Game::Game(int boardWidth, int boardHeight, bool useDisplay) : state{boardWidth, boardHeight}
{
    outputs.push_back(make_unique<TextDisplay>());
    if (useDisplay) {
        outputs.push_back(make_unique<Visualizer>(state));
    }
    
}

Game::~Game() {}

int Game::play(const string &player1, const string &player2)
{
    players.push_back(getPlayer(player1, 0));
    players.push_back(getPlayer(player2, 1));

    string cmd;
    cout << "DEBUG: Chess game start!" << endl;
    while (cin >> cmd)
    {
        if (cmd == "setup")
        {
            state.setup(*this);
        }
        else if (cmd == "move")
        {
            Move move = players[state.currentPlayer]->nextMove(state);
            // post: move is valid

            state.board->makeMove(move);
            history.addMove(move);

            state.switchPlayers();
            updateOutputs(move);
        }
        else if (cmd == "valid")
        {
            Position pos;
            cin >> pos;

            vector<Move> validMoves = state.getValidMoves(pos);

            cout << "You can move the piece at " << pos << " in " << validMoves.size() << " ways:" << endl;

            for (int i = 0; i < (int)validMoves.size(); ++i)
            {
                cout << validMoves[i] << endl;
            }
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
        cout << "DEBUG: Command complete! It's now player " << state.currentPlayer << "'s turn" << endl;
    }

    return -1;
}

void Game::updateOutputs(const Move &m) const
{
    for (auto &output : outputs)
    {
        output->update(state, m);
    }
}

unique_ptr<Player> Game::getPlayer(const string &playerName, int playerNum) const
{
    if (playerName == "human") {
        return make_unique<Human>(playerNum);
    } else if (playerName == "computer1") {
        return make_unique<Computer1>(playerNum);
    } else if (playerName == "computer2") {
        return make_unique<Computer2>(playerNum);
    } else if (playerName == "computer3") {
        return make_unique<Computer3>(playerNum);
    } else if (playerName == "computer4") {
        return make_unique<Computer4>(playerNum);
    } else {
        cout << "Invalid player name, assuming human" << endl;
        return make_unique<Human>(playerNum);
    }
}