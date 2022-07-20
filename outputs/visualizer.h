#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include "output.h"
#include "../graphics/sdl_wrap.h"

class GameState;

class Visualizer : public Output
{
    Visualizer(const GameState &);
    void doUpdate(const GameState &, const Move &) override;
}; 
#endif
