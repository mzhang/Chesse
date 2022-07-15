#include <iostream>
#include <memory>
#include "chess.h"
#include "./game/game.h"

using namespace std;

Chess::Chess() {}

Chess::~Chess() {}

void Chess::start()
{
    int boardWidth = 8;
    int boardHeight = 8;

    int player1Score = 0;
    int player2Score = 0;

    string cmd, player1, player2;
    while (cin >> cmd)
    {
        if (cmd == "game") {
            cin >> player1 >> player2;
            Game game{boardWidth, boardHeight};
            int winner = game.play(player1, player2);

            if (winner == 0) {
                player1Score++;
            }
            else {
                player2Score++;
            }

        } else if (cmd == "custom") {
            // TODO: allow custom setup such as modifying board size
            break;
        } else {
            cout << "Invalid command" << endl;
        }  
    }

    // print game results
    cout << "Final Score:" << endl;
    cout << "White: " << player1Score << endl;
    cout << "Black: " << player2Score << endl;
}

//   switch (cmd)
//         {
//         case 'n':
//             g = make_unique<Game>(boardWidth, boardHeight);
//             cin >> *g;
//             break;
//         case 'p':
//             g->play();
//             break;
//         case 'q':
//             return;
//         default:
//             cout << "Invalid command" << endl;