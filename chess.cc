#include <iostream>
#include "chess.h"
#include "./game/game.h"

using namespace std;

Chess::Chess() {}

Chess::~Chess() {}

void Chess::start()
{
    char cmd;
    while (cin >> cmd)
    {
        switch (cmd)
        {
        case 'n':
            g = new Game{};
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