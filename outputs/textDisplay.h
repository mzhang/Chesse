#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include "output.h"

struct Position;
class GameState;

class TextDisplay : public Output
{
    void doUpdate(const GameState &, const Move &) override;
}; 
#endif
