#ifndef BALL_HPP_
#define BALL_HPP_

#include "light.hpp"
#include <glm/glm.hpp>
#include <sphere.hpp>

class Ball : virtual public Movable,
             virtual public Light,
             virtual public Sphere {
public:
  Ball(const Ball &) = delete;
  Ball(Ball &&) = default;
  Ball &operator=(const Ball &) = delete;
  Ball &operator=(Ball &&) = delete;

  Ball(float radius = 0.04f);

private:
  float m_radius{};
};

#endif // BALL_HPP_
