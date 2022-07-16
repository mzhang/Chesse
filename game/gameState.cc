#include <memory>
#include "gameState.h"
#include "board.h"

using namespace std;

GameState::GameState(int boardWidth, int boardHeight) : board{make_unique<Board>(boardWidth, boardHeight)}, currentPlayer{0} {}