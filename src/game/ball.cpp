#include "ball.hpp"

Ball::Ball(float radius) : Sphere(radius), m_radius(radius) {
  setDiffuse(glm::vec3{.05f});
  setSpecular(glm::vec3{.05f});
}
