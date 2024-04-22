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
   * @brief Check wheather ball collides with border on the right side.
   */
  bool doesBallCollideBorderRight() const {
    if (m_ball->getPosition().x + m_ball->getRadius() >=
        m_gameLevel->getCollisonLinePositonRight()) {
      return true;
    }
    return false;
  }

  /**
   * @brief Check wheather ball collides with border on the left side.
   */
  bool doesBallCollideBorderLeft() const {
    if (m_ball->getPosition().x - m_ball->getRadius() <=
        m_gameLevel->getCollisonLinePositonLeft()) {
      return true;
    }
    return false;
  }

  bool doesBallCollideBorderTop() const {
    if (m_ball->getPosition().y + m_ball->getRadius() >=
        m_gameLevel->getCollisonLinePositonTop()) {
      return true;
    }
    return false;
  }

private:
  /**
   * @brief Collisons of ball from walls and bricks.
   */
  enum class BallCollison { horizontal, vertical };

  /**
   * @param collisonSide Which side ball hit.
   *
   * @return vector of ball movement after collison with obstile on direction
   */
  glm::vec3 ballVectorAfterCollision(BallCollison collisonDirection);

  /**
   * @brief Find collsion vector if collisons occurs
   *
   * @retunrs Collison surface normal vector, or {0,0,0} vector if no collison
   * occured.
   * */
  glm::vec3 findBallCollisonVector() const;

  /**
   * @brief Perform ball collison with surface
   * @param normal Normal vector of surface hit.
   */
  void performBallReflect(glm::vec3 normal) {
    auto n{glm::normalize(normal)};
    m_ballMovementVector = glm::reflect(m_ballMovementVector, normal);
  }

  /**
   * @brief Ball in the game.
   */
  std::shared_ptr<Ball> m_ball;

  /**
   * @brief Normalized ballMovmentVector
   */
  glm::vec3 m_ballMovementVector{glm::vec3{1.f, 0.1f, 0.f}};

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
  float m_ballspeed{0.005};
};

#endif // GAME_HPP_
