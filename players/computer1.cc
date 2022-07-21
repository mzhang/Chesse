#include "computer1.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "../game/board.h"

Computer1::Computer1(int playerNum) : Player{playerNum}
{
}

Move Computer1::doNextMove(const GameState &state)
{
    // Iterates over all pieces and all possible moves for each piece in gamestate's board
    // randomly chooses one and returns it

}