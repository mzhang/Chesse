#ifndef CHESS_DRAWING_H_
#define CHESS_DRAWING_H_

#include "sdl_wrap.h"
#include "../data/move.h"
#include "../game/game.h"
#include "../data/pieceType.h"

class ChessDrawing
{
public:
    void draw_game(Screen &screen, const Game &game);
    void draw_chessboard_background(Screen &screen);
    void draw_chesspiece(Screen &screen, int r, int c, PieceType piece, bool black);
    void draw_timer(Screen &screen, int time);
    void draw_axes(Screen &screen);
    void draw_potential_moves(Screen &screen, const std::vector<Move> &moves);
};

#endif // CHESS_DRAWING_H_