#include "visualizer.h"
#include "../game/gameState.h"
#include "../game/board.h"
#include "../data/pieceType.h"
#include "../graphics/sdl_wrap.h"
#include "../data/move.h"

#include "../data/position.h"
#include "../graphics/chess_drawing.h"

#include <memory>

using namespace std;

bool Visualizer::SDLIsInitialized = false;

void Visualizer::initializeSDL()
{
    if (!SDLIsInitialized)
    {
        SDLIsInitialized = true;
        SDL_Runner runner;
    }
}

Visualizer::Visualizer(const GameState &state)
{
    // Initialize SDL and create a screen
    initializeSDL();
    screen = make_unique<Screen>();

    // Draw game board
    ChessDrawing::draw_chessboard_background(*screen);

    // Draw all pieces
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Position p{r,c};
            PieceType piece = state.board->getPieceType(p);
            int owner = state.board->getOwner(p);
            ChessDrawing::draw_chesspiece(*screen, r, c, piece, owner);
        }
    }

}

void Visualizer::doUpdate(const GameState &b, const Move &m) {
    // TODO: implement

    // Draw all the changes from move
    

}