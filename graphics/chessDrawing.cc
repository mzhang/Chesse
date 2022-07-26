#include "chessDrawing.h"

#include "screen.h"
#include "colours.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "../data/pieceType.h"

void ChessDrawing::draw_chessboard_background(Screen &screen)
{
    // Draw wooden color border
    screen.draw_rect(0, 0, screen.getWidth(), screen.getHeight(), BROWN);
}

void ChessDrawing::draw_axes(Screen &screen)
{
    // Write row letters (chess)
    for (int i = 0; i < 8; i++)
    {
        screen.draw_text(20, (7 - i) * square_size + y_offset + 20, 50, 50, std::to_string((i + 1)), 20, WHITE);
    }
    // Write column numbers (chess)
    for (int i = 0; i < 8; i++)
    {
        screen.draw_text(i * square_size + x_offset + 25, screen.getHeight() - 40, 50, 50, std::string(1, (char)('A' + i)), 20, WHITE);
    }
}

void ChessDrawing::clear_square(Screen &screen, int x, int y)
{
    // Clear chessboard square x, y and return to background color
    y = 7 - y;

    if ((x + y) % 2 == 0)
    {
        screen.draw_rect(x * square_size + x_offset, y * square_size + y_offset, square_size, square_size, WHITE);
    }
    else
    {
        screen.draw_rect(x * square_size + x_offset, y * square_size + y_offset, square_size, square_size, BLACK);
    }
}

void ChessDrawing::draw_potential_moves(Screen &screen, const std::vector<Move> &moves)
{
    // Draw a small square on each square corresponding to move.to in each move in moves
    int indicator_size = square_size / 4;
    for (const Move &move : moves)
    {
        for (const Position &pos : move.to)
        {
            screen.draw_rect(pos.x * square_size + x_offset, pos.y * square_size + y_offset,
                             indicator_size, indicator_size, WHITE);
        }
    }
}

void ChessDrawing::draw_valid_position(Screen &screen, int x, int y)
{
    // The indicator is stored in greenDot.png, the size is 20 x 20
    std::string filename = "greenDot.png";
    screen.draw_image(x * square_size + x_offset + 25, (7-y) * square_size + y_offset + 25, 20, 20, filename);
}

void ChessDrawing::draw_chesspiece(Screen &screen, int x, int y, PieceType piece, PlayerColor owner)
{
    // Draw a chesspiece on the square at (r, c). Load image from resources folder
    // Files are stored in the format [pieceName]_sprite.png
    std::string filename = PieceTypeUtils::toString(piece, owner);
    filename += "_sprite.png";
    screen.draw_image(x * square_size + piece_x_offset, (7 - y) * square_size + piece_y_offset, square_size, square_size, filename);
}
