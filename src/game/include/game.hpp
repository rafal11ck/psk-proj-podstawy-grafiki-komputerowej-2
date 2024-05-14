#ifndef GAME_HPP_
#define GAME_HPP_

#include "ball.hpp"
#include "gameLevel.hpp"
#include "palette.hpp"
#include "scoreBar.hpp"
#include <memory>

class Game : public Drawable {
public:
  Game(const Game &) = delete;
  Game(Game &&) = default;
  Game &operator=(const Game &) = delete;
  Game &operator=(Game &&) = default;

  Game(std::shared_ptr<Ball> ball);

  /**
   * @brief movementDirections
   *
   * @Note Should use default values as it is used for indicies.
   */
  enum class MovementDirection {
    front,
    back,
    left,
    right,
    max_movementDirection
  };

  void draw(Shader &shader) override;

  /**
   * @brief Process game logic
   * @param dt Time in seconds;
   */
  void update(const float dt);

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

  void setBallMovementVector(glm::vec3 vector);

  void setBallSpeed(float speed);

  /**
   * Wheather pallete moves in given direction.
   */
  void setPalleteMovementState(MovementDirection movementDirection, bool state);

  /**
   * @brief Get vector of movement in given direction.
   * @param movementDirection direction of movement.
   * @returns Normalized vector of movement direction
   */
  glm::vec3 getVector(MovementDirection movementDirection) const;

  /**
   * @brief Get movement vector of pallete.
   * @returns Normalized movemnet vector of pallete if it moves.
   */
  std::optional<glm::vec3> getPalleteMovmentVector() const;

private:
  /**
   * @brief Process ball movement.
   *
   * @param dt Time in seconds.
   */
  void processBallMovement(const float dt);

  /**
   * @brief Process pallete movement.
   * @param dt Time in seconds.
   */
  void processPalleteMovement(float dt);

  /**
   * Check weather pallete should move in given driection.
   *
   * @Note Does not ceeck for canceling moves. As in moves left and right
   * canceling each other but returns true for both;
   */
  bool isPalleteMoving(MovementDirection direction) const;

  /**
   * @brief Brick collisons
   */
  void handleBrickCollisions();

  /**
   * @brief Resolve collison with Brick
   * @param brick Brick hit.
   * @param cllisonPoint Collison point.
   */
  void resolveBrickCollison(Brick &brick, glm::vec3 collisonPoint);

  /**
   * @brief Perform ball collision with surface
   * @param normal Normal vector of surface hit.
   *
   * Changes m_ballMovementVector to reflect bounce.
   */
  void performBallReflect(glm::vec3 normal);

  /**
   * @brief Handles Ball collsios with pallete.
   */
  void handlePalleteCollisons();

  /**
   * @brief Handle collisions why any objects.
   */
  void handleCollisions();

  void addScore(long points);

  /**
   * @brief check weather ball is out of map in a way player would lose.
   */
  bool isBallOutOfMap() const;

  /**
   * @brief Check weather game is done.
   */
  bool isGameOver() const;

  /**
   * @brief moves given ball above pallete
   */
  void moveBallAbovePallete(Ball *ball);
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
   * @brief State of pallete movment.
   *
   * true if is moving in given direction
   * MovementDirection indicates directions of movment
   */
  std::vector<bool> m_palleteMoves{std::vector<bool>(
      static_cast<ssize_t>(MovementDirection::max_movementDirection), false)};

  /**
   * @brief speed of ball.
   */
  float m_ballMovementSpeed{0.005};

  /**
   * @brief Speed of pallete
   */
  float m_palletteMovementSpeed{1};

  ScoreBar m_scoreBar{};
};

#endif // GAME_HPP_
