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
#include "../data/playerColor.h"

using namespace std;

Game::Game(int boardWidth, int boardHeight, bool useDisplay) : state{boardWidth, boardHeight}, history{state}
{
    outputs.push_back(make_unique<TextDisplay>());
    if (useDisplay)
    {
        outputs.push_back(make_unique<Visualizer>(state));
    }
}

Game::~Game() {}

PlayerColor Game::play(const string &player1, const string &player2)
{
    players[PlayerColor::WHITE] = getPlayer(player1, PlayerColor::WHITE);
    players[PlayerColor::BLACK] = getPlayer(player2, PlayerColor::BLACK);

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

            history.addMove(move, state);
            if (state.isValidMove(move))
            {
                state.makeMove(move, players[state.currentPlayer]->isHeadless());
                state.switchPlayers();
                updateOutputs(move);
            }
            else
            {
                cout << "Invalid move" << endl;
            }
        }
        else if (cmd == "undo")
        {
            // Get last gamestate from history and replace gamestate if available
            if (!history.empty())
            {
                auto move_state = history.pop_back();
                state = move_state.second;
                updateOutputs(move_state.first);
            }
            else
            {
                cout << "No moves to undo." << endl;
            }
        }
        else if (cmd == "valid")
        {
            Position pos;
            cin >> pos;

            vector<Move> validMoves = state.getValidMoves(pos);

            if (validMoves.size() > 0)
            {
                for (auto &output : outputs)
                {
                    output->displayValidMoves(state, validMoves);
                }
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

    return PlayerColor::NONE;
}

void Game::updateOutputs(const Move &m) const
{
    for (auto &output : outputs)
    {
        output->update(state, m);
    }
}

unique_ptr<Player> Game::getPlayer(const string &playerName, PlayerColor playerColor) const
{
    if (playerName == "human")
    {
        return make_unique<Human>(playerColor);
    }
    else if (playerName == "computer1")
    {
        return make_unique<Computer1>(playerColor);
    }
    else if (playerName == "computer2")
    {
        return make_unique<Computer2>(playerColor);
    }
    else if (playerName == "computer3")
    {
        return make_unique<Computer3>(playerColor);
    }
    else if (playerName == "computer4")
    {
        return make_unique<Computer4>(playerColor);
    }
    else
    {
        cout << "Invalid player name, assuming human" << endl;
        return make_unique<Human>(playerColor);
    }
}