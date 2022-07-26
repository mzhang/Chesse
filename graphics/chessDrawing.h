#ifndef CHESS_DRAWING_H_
#define CHESS_DRAWING_H_

#include <vector>

class Screen;
struct Move;
enum class PieceType;
class GameState;
enum class PlayerColor;
class Position;

class ChessDrawing {
  static const int square_size = (652 - 100) / 8;
  static const int x_offset = 50;
  static const int y_offset = 50;
  static const int piece_x_offset = x_offset + 6;
  static const int piece_y_offset = y_offset + 4;

public:
  // static void draw_game(Screen &screen, const GameState &state);
  static void draw_axes(Screen &screen);
  static void draw_chesspiece(Screen &screen, int, int, PieceType piece,
                              PlayerColor owner);
  static void draw_chessboard_background(Screen &screen);
  static void draw_potential_moves(Screen &screen,
                                   const std::vector<Move> &moves);
  static void clear_square(Screen &screen, int, int);
  static void draw_valid_position(Screen &screen, int, int);
};

#endif // CHESS_DRAWING_H_
