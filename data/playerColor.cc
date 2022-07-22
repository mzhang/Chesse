#include <iostream>
#include "playerColor.h"

using namespace std;

PlayerColor PlayerColorUtils::getNext(PlayerColor c)
{
    return static_cast<PlayerColor>((static_cast<int>(c) + 1) % playerNum);
}

PlayerColor PlayerColorUtils::getPrevious(PlayerColor c)
{
    return static_cast<PlayerColor>((static_cast<int>(c) - 1) % playerNum);
}

int getInt(PlayerColor c)
{
    return static_cast<int>(c);
}

ostream &operator<<(ostream &os, const PlayerColor &c)
{
    switch (c)
    {
    case PlayerColor::WHITE:
        os << "WHITE";
        break;
    case PlayerColor::BLACK:
        os << "BLACK";
        break;
    case PlayerColor::NONE:
        os << "NONE";
        break;
    }
    return os;
}

PlayerColor PlayerColorUtils::fromString(const std::string &s)
{
    if (s == "WHITE")
    {
        return PlayerColor::WHITE;
    }
    else if (s == "BLACK")
    {
        return PlayerColor::BLACK;
    }
    else
    {
        return PlayerColor::NONE;
    }
}