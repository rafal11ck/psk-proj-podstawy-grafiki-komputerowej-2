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
   * @brief Process game logic
   * @param dt Time.
   */
  void update(const float dt);

  /**
   * @brief Process ball movement.
   *
   * @param dt Time.
   */
  void processBallMovement(const float dt);

  /**
   * @brief Set game level.
   * @param gameLevel level to set.
   */
  void setGameLevel(std::unique_ptr<GameLevel> gameLevel) {
    m_gameLevel = std::move(gameLevel);
  }

  /**
   * @brief Get normal vector of map border hit if any.
   *
   * @return Normal vector of hit surface or {0,0,0};
   */
  glm::vec3 mapBordersCollision() const;

private:
  void handleBrickCollisions();

  /**
   * @brief Perform ball collision with surface
   * @param normal Normal vector of surface hit.
   *
   * Changes m_ballMovementVector to reflect bounce.
   */
  void performBallReflect(glm::vec3 normal) {
    auto n{glm::normalize(normal)};
    m_ballMovementVector = glm::reflect(m_ballMovementVector, normal);
  }

  /**
   * @brief Handle collisions why any objects.
   */
  void handleCollisions();

  /**
   * @brief Ball in the game.
   */
  std::shared_ptr<Ball> m_ball;

  /**
   * @brief Normalized ballMovementVector
   */
  glm::vec3 m_ballMovementVector{glm::vec3{1.f, 0.1f, 0.f}};

  /**
   * @brief Game level in the game.
   */
  std::unique_ptr<GameLevel> m_gameLevel{std::make_unique<GameLevel>()};

  /**
   * @brief Palette in the game.
   */
  Pallette m_palette{};

  /**
   * @brief speed of ball.
   */
  float m_ballSpeed{0.005};
};

#endif // GAME_HPP_
