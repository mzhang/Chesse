#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include "output.h"
#include "../graphics/sdl_wrap.h"


#include <memory>

class GameState;
class Position;

class Visualizer : public Output
{
    std::unique_ptr<Screen> screen;
    static bool SDLIsInitialized;
    static void initializeSDL();
    void draw_position(const GameState &, const Position &);
    void doUpdate(const GameState &, const Move &) override;
public:
    explicit Visualizer(const GameState &);

    ~Visualizer();
}; 
#endif
