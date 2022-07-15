#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include "../game/board.h"
#include "output.h"
#include "../graphics/sdl_wrap.h"

class TextDisplay : public Output
{
    void doUpdate(Board &b) override;
}; 
#endif
