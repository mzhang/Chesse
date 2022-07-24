#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include "chess.h"
#include "./game/game.h"
#include "./data/playerColor.h"
using namespace std;

Chess::Chess()
{
}

Chess::~Chess() {}

void Chess::start(bool useDisplay)
{
    string cmd, player1, player2;
    while (cin >> cmd)
    {
        if (cmd == "game")
        {
            cin >> player1 >> player2;
            unordered_map<PlayerColor, string> players{
                {PlayerColor::WHITE, player1},
                {PlayerColor::BLACK, player2}
            };

            Game game{boardWidth, boardHeight, useDisplay, players};
            PlayerColor winner = game.play();

            cout << winner << " wins!" << endl;

            if (winner == PlayerColor::NONE)
            {
                for (const pair<PlayerColor, string> &player : players)
                {
                    playerScores[player.first] += 0.5;
                }
            }
            else
            {
                playerScores[winner] += 1;
            }
        }
        else if (cmd == "custom")
        {
            // TODO: allow custom setup such as modifying board size

            string custom_cmd;
            // Commands can be
            // - size <width> <height>

            while (cin >> custom_cmd)
            {
                if (custom_cmd == "size")
                {
                    string boardWidth, boardHeight;
                    cin >> boardWidth >> boardHeight;
                    // TODO: implement
                }
                else
                {
                    cout << "Unknown command: " << custom_cmd << endl;
                    break;
                }
            }

            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }

    // print game results
    cout << "Final Score:" << endl;
    for (auto &p : playerScores)
    {
        cout << p.first << ": " << p.second << endl;
    }
}