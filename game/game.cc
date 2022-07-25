#include <memory>
#include <utility>
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

Game::Game(int boardWidth, int boardHeight, bool useDisplay, unordered_map<PlayerColor, string> playerStrings) : state{boardWidth, boardHeight}, history{state}
{
    outputs.push_back(make_unique<TextDisplay>(boardWidth, boardHeight));
    if (useDisplay)
    {
        outputs.push_back(make_unique<Visualizer>(state, boardWidth, boardHeight));
    }
    for (const pair<PlayerColor, string> &player : playerStrings)
    {
        players[player.first] = getPlayer(player.second, player.first);
    }
}

Game::~Game() {}

PlayerColor Game::play()
{
    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "setup")
        {
            state.setup(*this);

            // we may end setup mode in stalemate
            pair<bool, PlayerColor> gameEnded = state.getStatus();
            if (gameEnded.first)
            {
                cout << (gameEnded.second == PlayerColor::NONE ? "Stalemate! " : "Checkmate! ");
                return gameEnded.second;
            }
        }
        else if (cmd == "move")
        {
            Move move = players[state.currentPlayer]->nextMove(state);

            // make sure there's no malformed moves. These should never happen, but just in case.
            if (move.from.size() == 0 || move.to.size() == 0 || move.from.size() != move.to.size() || move.from == move.to || !state.isValidMove(move))
            {
                throw runtime_error("Malformed move after nextMove called. Was there some malformed move in getValidMoves?");
            }
            
            history.addMove(move, state);
            state.makeMove(move, players[state.currentPlayer]->isHeadless());

            pair<bool, PlayerColor> gameEnded = state.getStatus();
            if (gameEnded.first)
            {
                cout << (gameEnded.second == PlayerColor::NONE ? "Stalemate! " : "Checkmate! ");
                return gameEnded.second;
            }

            state.switchPlayers();

            if (state.isInCheck(state.currentPlayer))
            {
                cout << state.currentPlayer << " is in check!" << endl;
            }

            updateOutputs(move);
        }
        else if (cmd == "undo")
        {
            // Get last gamestate from history and replace gamestate if available
            if (history.empty())
            {
                cout << "No moves to undo" << endl;
                continue;
            }
            pair<Move, GameState> move_state = history.pop_back();
            state = move_state.second;
            updateOutputs(move_state.first);
        }
        else if (cmd == "valid")
        {
            Position pos;
            while (cin >> pos) {
                if (state.isInBounds(pos))
                {
                    break;
                }
                
                cout << "Invalid position" << endl;
            }
            

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