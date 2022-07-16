#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include "../game/gameState.h"
#include "output.h"
#include "../graphics/sdl_wrap.h"

class TextDisplay : public Output
{
    void doUpdate(GameState &) override;
}; 
#endif
