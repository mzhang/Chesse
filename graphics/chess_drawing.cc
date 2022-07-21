#include "chess_drawing.h"

#include "sdl_wrap.h"
#include "sdl_colors.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "../data/pieceType.h"


void ChessDrawing::draw_chessboard_background(Screen &screen)
{
    // Draw wooden color border
    screen.draw_rect(0, 0, screen.getWidth(), screen.getHeight(), BROWN);

    // Draw an 8x8 chessboard background
    const int square_size = screen.getWidth() / 8 - 10; // buffer for background
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                screen.draw_rect(i * square_size + 5, j * square_size + 5, square_size, square_size, WHITE);
            }
            else
            {
                screen.draw_rect(i * square_size + 5, j * square_size + 5, square_size, square_size, BLACK);
            }
        }
    }
}

void ChessDrawing::draw_axes(Screen &screen)
{
    const int square_size = screen.getWidth() / 8 - 10;
    // Write row letters (chess)
    for (int i = 0; i < 8; i++)
    {
        screen.draw_text(2, i * square_size + 5, 5, 5, std::to_string(('A' + i)), 10, WHITE);
    }
    // Write column numbers (chess)
    for (int i = 0; i < 8; i++)
    {
        screen.draw_text(i * square_size + 5, 2, 5, 5, std::to_string((i + 1)), 10, WHITE);
    }
}

void ChessDrawing::clear_square(Screen &screen, int x, int y) {
    // Clear chessboard square x, y and return to background color
    int square_size = screen.getWidth() / 8 - 10;
    if ((x + y) % 2 == 0)
    {
        screen.draw_rect(x * square_size + 5, y * square_size + 5, square_size, square_size, WHITE);
    }
    else
    {
        screen.draw_rect(x * square_size + 5, y * square_size + 5, square_size, square_size, BLACK);
    }
}

void ChessDrawing::draw_potential_moves(Screen &screen, const std::vector<Move> &moves)
{
    const int square_size = screen.getWidth() / 8 - 10;
    // Draw a small square on each square corresponding to move.to in each move in moves
    int indicator_size = square_size / 4;
    for (const Move &move : moves)
    {
        for (const Position &pos : move.to)
        {
            screen.draw_rect(pos.x * square_size + 5, pos.y * square_size + 5, indicator_size, indicator_size, WHITE);
        }
    }
}

void ChessDrawing::draw_chesspiece(Screen &screen, int x, int y, PieceType piece, int owner)
{
    const int square_size = screen.getWidth() / 8 - 10;
    // Draw a chesspiece on the square at (r, c). Load image from resources folder
    // Files are stored in the format [pieceName]_sprite.png
    std::string filename = PieceTypeUtils::toString(piece, owner);
    filename += "_sprite.png";

    screen.draw_image(x * square_size + 5, y * square_size + 5, square_size, square_size, filename);
}