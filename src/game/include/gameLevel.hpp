#ifndef GAMELEVEL_HPP_
#define GAMELEVEL_HPP_

#include "ball.hpp"
#include "brick.hpp"
#include <optional>
#include <vector>

class GameLevel : public virtual Drawable {
public:
  GameLevel(const GameLevel &) = delete;
  GameLevel(GameLevel &&) = default;
  GameLevel &operator=(const GameLevel &) = delete;
  GameLevel &operator=(GameLevel &&) = default;

public:
  GameLevel(int rowCount = 2, int columnCount = 4);

  ~GameLevel();

  void draw(Shader &shader) override;

  void setBricksHeight(float height);

  /**
   * @brief positon of left collison line.
   */
  float getCollisonLinePositonLeft() const;

  /**
   * @brief positon of right collison line.
   */
  float getCollisionLinePositionRight() const;

  /**
   * @brief positon of top collsion line.
   */
  float getCollisonLinePositonTop() const {
    return getBricksStartingPostion().second;
  };

  const std::pair<std::optional<std::reference_wrapper<Brick>>, glm::vec3>
  findCollidingBrick(const Ball &);

private:
  int m_bricksRowCount{2};
  int m_bricksColumnCount{3};

  float m_brickHeight{0.1};

  float m_paddingBricksTop{0};
  float m_paddingBricksSide{0};

  std::vector<std::vector<Brick>> m_bricks{};

  /**
   * @brief Update bricks data
   *
   * Updates postions and sizes of bricks.
   */
  void updateBricks();

  /**
   * @brief Set brick's sizes (scale).
   */
  void setBrickSizes();

  /**
   * @brief Set brick's postions.
   */
  void setBrickPostions();

  /**
   * @brief Compute width of single brick
   */
  float getBrickWidth() const;

  /**
   * @brief How much space on screen brick takes.
   */
  float getBrickHeight() const;

  /**
   * @brief Compute where should origin of brick be.
   * */
  std::pair<float, float> computeBrickPositionOrigin(int column, int row) const;

  /**
   * @brief Compute where left top corner of bricks should be.
   * */
  std::pair<float, float> getBricksStartingPostion() const;

  float getBricksHorizontalSpace() const;

  std::optional<glm::vec3> findCollisonPoint(const Ball &ball,
                                             const Cube *cube) const;

  glm::vec3 findNearestPointOnContour(const Ball &ball, const Cube *cube) const;
};
#endif // GAMELEVEL_HPP_
