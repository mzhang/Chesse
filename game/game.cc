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
#include "../players/ComputerN.h"
#include "../data/playerColor.h"
#include "../data/completedMove.h"
#include "../players/computerFactory.h"

using namespace std;

Game::Game(int boardWidth, int boardHeight, bool useDisplay, unordered_map<PlayerColor, string> playerStrings) : state{boardWidth, boardHeight}
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

            CompletedMove completedMove = state.makeMove(move, players[state.currentPlayer]->isHeadless());
            history.addMove(std::move(completedMove));

            state.switchPlayers();

            updateOutputs(move);
            if (state.isInCheck(state.currentPlayer))
            {
                cout << state.currentPlayer << " is in check!" << endl;
            }

            pair<bool, PlayerColor> gameEnded = state.getStatus();
            if (gameEnded.first)
            {
                cout << (gameEnded.second == PlayerColor::NONE ? "Stalemate! " : "Checkmate! ");
                return gameEnded.second;
            }
        }
        else if (cmd == "undo")
        {
            // Get last gamestate from history and replace gamestate if available
            if (history.empty())
            {
                cout << "No moves to undo." << endl;
                continue;
            }
            CompletedMove lastMove = history.pop_back();
            state.undoMove(std::move(lastMove), history.getLastMove());
            state.currentPlayer = PlayerColorUtils::getPrevious(state.currentPlayer);
            updateOutputs(lastMove.move);
        }
        else if (cmd == "valid")
        {
            Position pos;
            while (cin >> pos)
            {
                if (state.isInBounds(pos))
                {
                    break;
                }

                cout << "Invalid position! Position:" << pos << endl;
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
            cout << "Invalid command! Command:" << cmd << endl;
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
        return ComputerFactory::createComputer(playerColor, 3);
    }
    else if (playerName == "computerN") {
        int movesLookAhead;
        cin >> movesLookAhead;
        return ComputerFactory::createComputer(playerColor, movesLookAhead);
    }
    else
    {
        cout << "Invalid player type entered! Assuming human player." << endl;
        return make_unique<Human>(playerColor);
    }
}