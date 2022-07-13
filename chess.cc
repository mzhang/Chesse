#include <iostream>
#include <memory>
#include "chess.h"
#include "./game/game.h"

using namespace std;

Chess::Chess() {}

Chess::~Chess() {}

void Chess::start()
{
    const int boardWidth = 8;
    const int boardHeight = 8;

    char cmd;
    while (cin >> cmd)
    {
        switch (cmd)
        {
        case 'n':
            g = make_unique<Game>(Game{boardWidth, boardHeight});
            cin >> *g;
            break;
        case 'p':
            g->play();
            break;
        case 'q':
            return;
        default:
            cout << "Invalid command" << endl;
        }
    }
}