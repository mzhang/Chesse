#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include "output.h"
#include "../graphics/screen.h"
#include "../data/move.h"

#include <memory>
#include <vector>

class GameState;
class Position;

class Visualizer : public Output
{
    std::unique_ptr<Screen> screen;

    std::vector<Move> validMoves; // used to clear valid move display after a move is made

    static bool SDLIsInitialized;
    static void initializeSDL();
    void draw_position(const GameState &, const Position &);
    void doUpdate(const GameState &, const Move &) override;
    void doDisplayValidMoves(const GameState &, const std::vector<Move> &) override;
public:
    explicit Visualizer(const GameState &);

    ~Visualizer();
}; 
#endif
