#ifndef BRICK_HPP_
#define BRICK_HPP_

#include "cube.hpp"
#include "drawable.hpp"
#include "fileSystem.hpp"

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
   * @biref default state of m_isActive.
   *
   * @note Needed for reset.
   */
  const bool m_isActiveDefaultState{true};

  /**
   * @brief Is brick on?
   *
   * If brick is not active it is not on the map.
   */
  bool m_isActive{m_isActiveDefaultState};

  Cube m_model{Texture{Texture::TextureType::diffuse,
                       FileSystem::getResourcesPath() + "/brick.png"}};

  glm::vec3 m_positionOrigin{};

  glm::vec3 m_size{1.f, 1.f, 1.f};

public:
  Brick();
  explicit Brick(Cube m_model);
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

  void setSize(glm::vec3 size);

  const glm::vec3 &getPositonOrigin() const;

  /**
   * @brief Get durability of brick.
   */
  int getDurability() const;

  /**
   * @brief Enables Brick.
   */
  void enable();

  /**
   * @brief Disables Brick.
   */
  void disable();

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
   * @param damage How much damage brick should take. It will take less damage
   * if it's durability would go under 0;
   * @return How much damage brick actually took.
   */
  int damage(int damage = 1);

  /**
   * @brief Disable if it has no durability left
   */
  void disableIfHasNoDurability();

  [[deprecated("Bad prattice getter to implemetation details breaks isolation "
               "priciple, rquireres "
               "rewrite")]] Cube &
  getModel();

  /**
   * @brief Reset durability of brick to it's max durability
   */
  void reset();

private:
  void updateModel();
  void updateModelScale();
  void updateModelPosition();
};

#endif // BRICK_HPP_
