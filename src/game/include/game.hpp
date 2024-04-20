#ifndef GAME_HPP_
#define GAME_HPP_

class Game {
public:
  Game(const Game &) = delete;
  Game(Game &&) = default;
  Game &operator=(const Game &) = delete;
  Game &operator=(Game &&) = default;
};

#endif // GAME_HPP_
