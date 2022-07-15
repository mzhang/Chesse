#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include "../game/board.h"
#include "output.h"
#include "../graphics/sdl_wrap.h"

class Visualizer : public Output
{
    Screen s;
    void doUpdate(Board &b) override;
}; 
#endif
