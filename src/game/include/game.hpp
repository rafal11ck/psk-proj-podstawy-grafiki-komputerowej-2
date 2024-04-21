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

  /**
   * @brief Process in game events.
   *
   */
  void update(float dt) {}

  /**
   * @brief Set game level.
   * @param gameLevel level to set.
   */
  void setGameLevel(std::unique_ptr<GameLevel> gameLevel) {
    m_gameLevel = std::move(gameLevel);
  }

private:
  /**
   * @brief Ball in the game.
   */
  std::shared_ptr<Ball> m_ball;

  /**
   * @brief Game level in the game.
   */
  std::unique_ptr<GameLevel> m_gameLevel{std::make_unique<GameLevel>()};

  /**
   * @brief Pallete in the game.
   */
  Pallette m_pallette{};

  /**
   * @brief speed of ball.
   */
  float m_ballspeed{0.05};
};

#endif // GAME_HPP_
