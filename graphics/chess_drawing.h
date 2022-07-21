#ifndef CHESS_DRAWING_H_
#define CHESS_DRAWING_H_

#include <vector>

class Screen;
struct Move;
enum class PieceType;
class GameState;

class ChessDrawing
{
public:
    // static void draw_game(Screen &screen, const GameState &state); 
    static void draw_axes(Screen &screen);
    static void draw_chesspiece(Screen &screen, int, int, PieceType piece, int owner);
    static void draw_chessboard_background(Screen &screen);
    static void draw_potential_moves(Screen &screen, const std::vector<Move> &moves);
    static void clear_square(Screen &screen, int, int);
};

#endif // CHESS_DRAWING_H_