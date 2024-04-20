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
  GameLevel(int rowCount = s_rowCount, int columnCount = s_columnCount);

  ~GameLevel();

  /**
   * @brief Set brick's sizes (scale).
   */
  void scaleBricks();

  /**
   * @brief Set brick's postions.
   */
  void setPostions();

  virtual void draw(Shader &shader) override;

protected:
  /**
   * @brief Padding of bricks from sides of screen.
   */
  static float s_borderPaddingSide;

  /**
   * @brief Padding of bricks from top of screen.
   */
  static float s_borderPaddingTop;

  /**
   * @brief How muchg space on screen brick takes.
   */
  static float s_brickHeight;

  /**
   * @brief How many columns are in row.
   */
  static int s_columnCount;
  /**
   * @ brief How many rows there are.
   */
  static int s_rowCount;

  /**
   *
   */

private:
  std::vector<std::vector<Brick>> m_bricks;

  int m_rowCount;
  int m_columnCount;

  /**
   * @brief Compute width of single brick
   */
  float brickWidth() const;

  float bricksVericalScreenSpace() const;

  /**
   * @brief Compute height of single brick
   */
  float brickHeight() const;
};

#endif // GAMELEVEL_HPP_
