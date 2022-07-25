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
                {PlayerColor::BLACK, player2}};

            Game game{boardWidth, boardHeight, useDisplay, players};
            PlayerColor winner = game.play();

            if (winner == PlayerColor::NONE)
            {
                for (const pair<PlayerColor, string> &player : players)
                {
                    playerScores[player.first] += 0.5;
                }
                cout << endl;
            }
            else
            {
                cout << winner << " wins!" << endl;
                playerScores[winner] += 1;
            }
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