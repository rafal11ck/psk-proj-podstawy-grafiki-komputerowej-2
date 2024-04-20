#ifndef GAMELEVEL_HPP_
#define GAMELEVEL_HPP_

#include "brick.hpp"
#include <vector>

class GameLevel : public virtual Drawable {
public:
  GameLevel(const GameLevel &) = delete;
  GameLevel(GameLevel &&) = default;
  GameLevel &operator=(const GameLevel &) = delete;
  GameLevel &operator=(GameLevel &&) = default;

public:
  GameLevel(int rowCount, int columnCount);

  ~GameLevel();

  /**
   * @brief Set brick's sizes (scale).
   */
  void scaleBricks();

  /**
   * @brief Set brick's postions.
   */
  void setPostions();

  void draw(Shader &shader) override;

private:
  int m_bricksRowCount{3};
  int m_bricksColumnCount{7};

  float m_brickHeight{0.1};

  float m_paddingBricksTop{0};
  float m_paddingBricksSide{0};

  std::vector<std::vector<Brick>> m_bricks{};

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
};

#endif // GAMELEVEL_HPP_
