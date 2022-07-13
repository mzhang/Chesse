#include "chess_drawing.h"
#include "sdl_wrap.h"
#include "sdl_colors.h"

void ChessDrawing::draw_chessboard_background(Screen &screen) {
    // Draw an 8x8 chessboard background
    const int width = screen.getWidth();
    const int height = screen.getHeight();
    const int square_size = std::min(width, height) / 8;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                screen.draw_rect(i * square_size, j * square_size, square_size, square_size, WHITE);
            } else {
                screen.draw_rect(i * square_size, j * square_size, square_size, square_size, BLACK);
            }
        }
    }
}