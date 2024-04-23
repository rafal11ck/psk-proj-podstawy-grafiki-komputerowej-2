#include "brick.hpp"
#include <log.hpp>

void Brick::draw(Shader &shader) { m_model.draw(shader); }

Brick::Brick() { LOGTRACEN; };

Brick::~Brick(){};

void Brick::updateModelScale() { m_model.setScale(0.5f * m_size); };

void Brick::updateModel() {
  updateModelScale();
  updateModelPosition();
};

const glm::vec3 &Brick::getPositonOrigin() const { return m_positionOrigin; }

const glm::vec3 &Brick::getSize() const { return m_size; };

void Brick::setIsImmuneTohits(bool immune) { m_isImmuneToHits = immune; }

void Brick::setPositionOrigin(glm::vec3 originPos) {
  m_positionOrigin = originPos;
  updateModel();
};

void Brick::updateModelPosition() { m_model.setPosition(m_positionOrigin); };
