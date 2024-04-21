#ifndef GAME_HPP_
#define GAME_HPP_

#include "ball.hpp"
#include "gameLevel.hpp"
#include "palette.hpp"
#include <memory>

class Game : public Drawable {
public:
  Game(const Game &) = delete;
  Game(Game &&) = default;
  Game &operator=(const Game &) = delete;
  Game &operator=(Game &&) = default;

  Game(std::shared_ptr<Ball> ball);

  void draw(Shader &shader) override;

private:
  /**
   * @brief Ball in the game.
   */
  std::shared_ptr<Ball> m_ball;

  /**
   * @brief Game level in the game.
   */
  std::unique_ptr<GameLevel> m_gameLevel{std::make_unique<GameLevel>()};

  Pallette m_pallette{};
};

#endif // GAME_HPP_
