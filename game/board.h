#ifndef BOARD_H_
#define BOARD_H_
#include <vector>

class Board
{
    const int width;
    const int height;

    std::vector<std::vector<char>> board;

public:
    Board(int, int);
    ~Board();
};

#endif
