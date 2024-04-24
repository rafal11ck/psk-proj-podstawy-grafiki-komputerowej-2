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
   * @brief Durability of brick
   */
  int m_durability{m_maxDurability};

  /**
   * @brief Can it have it's durability decresed.
   * */
  bool m_isDamageable{false};

  /**
   * @brief Is brick on?
   *
   * If brick is not active it is not on the map.
   */
  bool m_isActive{true};

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
  /**
   * @brief Get durability of brick.
   */
  int getDurability() const;

  /**
   * @brief Enables Brick.
   */
  void enable() { m_isActive = true; }

  /**
   * @brief Disables Brick.
   */
  void disable() { m_isActive = false; }

  /**
   * @brief Query weahter Brick is active.
   */
  bool isEnabled() const;

  /**
   * @brief Weather collison with brick is possible.
   *
   * For brick to be colidable it has to be active and have durability grater
   * than 0.
   */
  bool isCollidable() const;

  /**
   * @brief Damage brick
   * @param damage How much damage brick should take.
   * @param autoDisable Should brick get automatically disabled if it's
   * durability after hit is 0 or less.
   */
  void damage(int damage = 1, bool autoDisable = false);

  /**
   * @brief Disable if it has no durability left
   */
  void disableIfHasNoDurability() {
    if (m_durability <= 0)
      disable();
  }

private:
  void updateModel();
  void updateModelScale();
  void updateModelPosition();
};

#endif // BRICK_HPP_
