#ifndef BRICK_HPP_
#define BRICK_HPP_

#include "cube.hpp"
#include "drawable.hpp"

class GameLevel;

class Brick : public Drawable {
  /**
   * @brief How many hits can it take.
   */
  int m_maxDurability{1};

  /**
   * @brief durability of brick
   */
  int m_durability{m_maxDurability};

  /**
   * @brief Weather it can have it's durability damaged.
   * */
  bool m_isImmuneToHits{false};

  /**
   * @brief Weather Ball can hit it.
   */
  bool m_isHitable{true};

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

  void setIsImmuneTohits(bool immune);

  void setPositionOrigin(glm::vec3 originPos);

  void setSize(glm::vec3 size) {
    m_size = size;
    updateModel();
  }

  const glm::vec3 &getPositonOrigin() const;

  const glm::vec3 &getSize() const;

private:
  void updateModel();
  void updateModelScale();
  void updateModelPosition();
};

#endif // BRICK_HPP_
