#ifndef BRICK_HPP_
#define BRICK_HPP_

#include "cube.hpp"
#include "drawable.hpp"

class GameLevel;

class Brick : public Drawable {
  /**
   * @brief How many hits can it take.
   */
  int m_durability{1};

  glm::vec3 m_size{0.1f, 0.1f, 1.f};

  glm::vec3 m_positionOrigin;

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

  void setPositionOrigin(glm::vec3 originPos) {
    m_positionOrigin = originPos;
    updateModel();
  };

  void setSize(glm::vec3 size) {
    m_size = size;
    updateModel();
  }

protected:
  /**
   * @brief Trival getter for model
   * */
  Shape &getModel();

private:
  void updateModel();
  void updateModelScale();
  void updateModelPosition() { m_model.setPosition(m_positionOrigin); };
};

#endif // BRICK_HPP_
