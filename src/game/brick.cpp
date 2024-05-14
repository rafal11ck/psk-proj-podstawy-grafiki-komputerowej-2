#include "brick.hpp"
#include <log.hpp>

void Brick::draw(Shader &shader) {
  if (!m_isActive)
    return;
  m_model.draw(shader);
}

Brick::Brick() { LOGTRACEN; };

Brick::~Brick(){};

void Brick::updateModelScale() { m_model.setScale(0.5f * m_size); };

void Brick::updateModel() {
  updateModelScale();
  updateModelPosition();
};

const glm::vec3 &Brick::getPositonOrigin() const { return m_positionOrigin; }

void Brick::setIsImmuneTohits(bool immune) { m_isDamageable = immune; }

void Brick::updateModelPosition() { m_model.setPosition(m_positionOrigin); };

int Brick::getDurability() const { return m_durability; }

bool Brick::isEnabled() const { return m_isActive; }

bool Brick::isCollidable() const { return (m_isActive && m_durability > 0); }

int Brick::damage(int damage) {
  if (m_durability >= damage) {
    m_durability -= damage;
    return damage;
  } else {
    damage -= m_durability;
    return damage;
  }
}
