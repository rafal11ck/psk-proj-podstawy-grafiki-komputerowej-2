#ifndef BRICK_HPP_
#define BRICK_HPP_

#include "cube.hpp"
#include "drawable.hpp"

class GameLevel;

class Brick : public Drawable {
  friend GameLevel;
  /**
   * @brief How many hits can it take.
   */
  int m_durability{1};

  Cube m_model{};

public:
  Brick();
  ~Brick();

  Brick(const Brick &) = delete;
  Brick(Brick &&) = default;
  Brick &operator=(const Brick &) = delete;
  Brick &operator=(Brick &&) = default;
  /**
   * @brief Draw the object.
   */
  virtual void draw(Shader &shader) override;

protected:
  /**
   * @brief Trival getter for model
   * */
  Shape &getModel();
};

#endif // BRICK_HPP_
