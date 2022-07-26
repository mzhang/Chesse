#include "visualizer.h"
#include "../game/gameState.h"
#include "../game/board.h"
#include "../data/pieceType.h"
#include "../graphics/screen.h"
#include "../data/move.h"
#include "../data/playerColor.h"
#include "../data/position.h"
#include "../graphics/chessDrawing.h"

#include <memory>

using namespace std;

bool Visualizer::SDLIsInitialized = false;

void Visualizer::initializeSDL()
{
    if (!SDLIsInitialized)
    {
        SDLIsInitialized = true;
        SDL_Init(SDL_INIT_EVERYTHING);
    }
}

Visualizer::Visualizer(const GameState &state, int boardWidth, int boardHeight) : boardWidth(boardWidth), boardHeight(boardHeight)
{
    // Initialize SDL and create a screen
    initializeSDL();
    screen = make_unique<Screen>();

    // Draw game board
    ChessDrawing::draw_chessboard_background(*screen);
    ChessDrawing::draw_axes(*screen);

    // Draw all pieces
    for (int r = 0; r < boardHeight; r++)
    {
        for (int c = 0; c < boardWidth; c++)
        {
            Position p{r, c};
            draw_position(state, p);
        }
    }

    screen->update();
}

void Visualizer::draw_position(const GameState &b, const Position &position)
{
    ChessDrawing::clear_square(*screen, position.x, position.y);
    PieceType pieceType = b.getPieceType(position);
    if (pieceType != PieceType::NONE)
    {
        PlayerColor owner = b.getOwner(position);
        ChessDrawing::draw_chesspiece(*screen, position.x, position.y, pieceType, owner);
    }
}

void Visualizer::doUpdate(const GameState &b, const Move &m)
{
    // clear the valid move display
    for (auto move : validMoves)
    {
        for (auto p : move.to)
        {
            ChessDrawing::clear_square(*screen, p.x, p.y);
            draw_position(b, p);
        }
    }
    validMoves.clear();

    // Draw all the changes from move
    for (auto position : m.from)
    {
        draw_position(b, position);
    }

    for (auto position : m.to)
    {
        draw_position(b, position);
    }

    for (auto position : m.capturePositions)
    {
        draw_position(b, position);
    }

    screen->update();
}

void Visualizer::doDisplayValidMoves(const GameState &g, const vector<Move> &moves)
{
    // clear the valid move display
    for (auto move : validMoves)
    {
        for (auto p : move.to)
        {
            ChessDrawing::clear_square(*screen, p.x, p.y);
            draw_position(g, p);
        }
    }

    validMoves = moves;
    for (auto move : moves)
    {
        for (auto p : move.to)
        {
            ChessDrawing::draw_valid_position(*screen, p.x, p.y);
        }
    }
    screen->update();
}

Visualizer::~Visualizer()
{
    TTF_Quit();
    IMG_Quit();
    SDL_VideoQuit();
    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();
}