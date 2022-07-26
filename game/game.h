#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../players/player.h"
#include "gameHistory.h"
#include "gameState.h"

class Board;
class Output;

class Game {
  GameState state;
  GameHistory history;

  std::unordered_map<PlayerColor, std::unique_ptr<Player>> players;
  void switchPlayers();

  std::vector<std::unique_ptr<Output>> outputs;

public:
  Game();
  Game(int, int, bool, std::unordered_map<PlayerColor, std::string>);
  ~Game();
  PlayerColor play(); // returns winning player

  void updateOutputs(const Move &m = Move()) const;
  std::unique_ptr<Player> getPlayer(const std::string &, PlayerColor) const;
};

#endif
