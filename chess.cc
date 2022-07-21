#include <iostream>
#include <memory>
#include "chess.h"
#include "./game/game.h"

using namespace std;

Chess::Chess() {
    playerScores.resize(playerCount);
}

Chess::~Chess() {}

void Chess::start(bool useDisplay)
{
    string cmd, player1, player2;
    while (cin >> cmd)
    {
        if (cmd == "game") {
            cin >> player1 >> player2;
            Game game{boardWidth, boardHeight, useDisplay};
            int winner = game.play(player1, player2);
            if (winner != -1) {
                playerScores[winner]++;
            }
        } else if (cmd == "custom") {
            // TODO: allow custom setup such as modifying board size
    
            string custom_cmd;
            // Commands can be 
            // - size <width> <height>

            while (cin >> custom_cmd) {
                if (custom_cmd == "size") {
                    string boardWidth, boardHeight;
                    cin >> boardWidth >> boardHeight;
                    // TODO: implement
                } else {
                    cout << "Unknown command: " << custom_cmd << endl;
                    break;
                }
            }

            break;
        } else {
            cout << "Invalid command" << endl;
        }  
    }

    // print game results
    cout << "Final Score:" << endl;
    cout << "White: " << playerScores[0] << endl;
    cout << "Black: " << playerScores[1] << endl;
}