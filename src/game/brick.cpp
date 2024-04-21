#include "brick.hpp"
#include <log.hpp>

void Brick::draw(Shader &shader) { m_model.draw(shader); }

Brick::Brick() { LOGTRACEN; };

Shape &Brick::getModel() { return m_model; };

Brick::~Brick(){};

void Brick::updateModelScale() { m_model.setScale(0.5f * m_size); };

void Brick::updateModel() {
  updateModelScale();
  updateModelPosition();
};
