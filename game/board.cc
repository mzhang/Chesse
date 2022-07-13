#include <vector>
#include <memory>

#include "board.h"
#include "../moveable/moveable.h"

using namespace std;

void Board::resizeBoard() {
    board.resize(width);
    for (int i = 0; i < width; i++) {
        board[i].resize(height);
    }
}

Board::Board(int width, int height) : width{width}, height{height} {
    resizeBoard();
}

Board::~Board() {}

void Board::swap(Board &o)
{
    std::swap(width, o.width);
    std::swap(height, o.height);
    std::swap(board, o.board);
}

Board::Board(const Board &o) : width{o.width}, height{o.height} {
    resizeBoard();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Moveable* p = o.board[i][j].get();
            board[i][j] = unique_ptr<Moveable>(p);
        }
    }
}

Board &Board::operator=(const Board &o){
    Board tmp{o};
    swap(tmp);

    return *this;
}

Board::Board(Board &&o) : width{o.width}, height{o.height} {
    board = std::move(o.board);
    o.board.clear();
} 

Board &Board::operator=(Board &&o)
{
    swap(o);

    return *this;
}