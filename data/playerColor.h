#ifndef PLAYERCOLOR_H_
#define PLAYERCOLOR_H_

enum class PlayerColor
{
    WHITE,
    BLACK
};

struct PlayerColorUtils
{
    const static int playerNum = 2;
    static PlayerColor getNext(PlayerColor);
    static int getInt(PlayerColor);
};

#endif // PLAYERCOLOR_H_
