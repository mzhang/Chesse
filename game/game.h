#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include "gameState.h"
#include "gameHistory.h"
#include "../players/player.h"

class Board;
class Output;

class Game
{
    GameState state;
    GameHistory history;

    std::unordered_map<PlayerColor, std::unique_ptr<Player>> players;
    void switchPlayers();

    std::vector<std::unique_ptr<Output>> outputs;

public:
    Game();
    Game(int, int, bool);
    ~Game();
    PlayerColor play(const std::string &, const std::string &); // returns winning player

    void updateOutputs(const Move &m = Move()) const;
    std::unique_ptr<Player> getPlayer(const std::string &, PlayerColor) const;
};

#endif