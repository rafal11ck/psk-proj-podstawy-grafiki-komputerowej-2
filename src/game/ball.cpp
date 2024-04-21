#include "ball.hpp"

Ball::Ball() : m_model(m_radius){};

Shape &Ball::getModel() { return m_model; };

const glm::vec3 &Ball::getPos() const { return m_pos; };

void Ball::draw(Shader &shader) { m_model.draw(shader); }
