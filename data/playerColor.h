#ifndef PLAYERCOLOR_H_
#define PLAYERCOLOR_H_

#include <iostream>

enum class PlayerColor
{
    WHITE,
    BLACK,
    NONE
};

struct PlayerColorUtils
{
    const static int playerNum = 2;
    static PlayerColor getNext(PlayerColor);
    static PlayerColor getPrevious(PlayerColor);
    static int getInt(PlayerColor);
    static PlayerColor fromString(const std::string &);
};

std::ostream &operator<<(std::ostream &os, const PlayerColor &c);

#endif // PLAYERCOLOR_H_

