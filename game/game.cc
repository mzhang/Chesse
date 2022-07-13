#include <memory>
#include <iostream>
#include "game.h"
#include "board.h"
#include "../data/position.h"
#include "../moveable/moveX.h"
#include "../moveable/moveY.h"

using namespace std;

Game::Game(int boardWidth, int boardHeight) : boardWidth{boardWidth}, boardHeight{boardHeight},
                                              board{make_unique<Board>(boardWidth, boardHeight)} {}

Game::~Game() {}

void Game::play()
{
    cout << "Playing Game" << endl;
}

Game::Game(const Game &o) : boardWidth{o.boardWidth}, boardHeight{o.boardHeight}, board{make_unique<Board>(*o.board)} {}

std::istream &operator>>(std::istream &in, const Game &g)
{
    char cmd;
    int x, y;
    while (in >> cmd)
    {
        switch (cmd)
        {
            case 'a': // add blank piece to x, y
                cin >> x >> y;
                g.board->addPiece(x, y);
                break;
            case 'x': // TODO: find some system to choose what rule to apply
                cin >> x >> y;
                g.board->setPiece(x, y, new MoveX{g.board->getPiece(x, y)});
                break;
            case 'y':
                cin >> x >> y;
                g.board->setPiece(x, y, new MoveY{g.board->getPiece(x, y)}); // TODO: get proper rule to apply
                break;
            case 'v': // print valid moves for piece
                cin >> x >> y;
                for (auto &p : g.board->getValidMoves(x, y))
                {
                    cout << p << "; ";
                }
                cout << endl;

                break;
            case 'q':
                return in;
            default:
                cout << "Invalid command" << endl;
                break;
        }
    }

    return in;
}

std::ostream &operator<<(std::ostream &out, const Game &g)
{
    out << "Printing Game" << endl;

    return out;
}