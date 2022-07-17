#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include "output.h"

class Position;
class GameState;

class TextDisplay : public Output
{
    void doUpdate(const GameState &) override;
}; 
#endif
