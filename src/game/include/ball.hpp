#ifndef BALL_HPP_
#define BALL_HPP_

#include <glm/glm.hpp>
#include <sphere.hpp>

class Ball : virtual public Drawable {
public:
  Ball(const Ball &) = delete;
  Ball(Ball &&) = default;
  Ball &operator=(const Ball &) = delete;
  Ball &operator=(Ball &&) = default;

  Ball();

  Shape &getModel();

  const glm::vec3 &getPos() const;

  void draw(Shader &shader) override;

private:
  glm::vec3 m_pos{};

  float m_radius{0.05};

  Sphere m_model{};
};

#endif // BALL_HPP_
