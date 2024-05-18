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
void Brick::disableIfHasNoDurability() {
  if (m_durability <= 0) {
    disable();
  }
}

Cube &Brick::getModel() { return m_model; };

Brick::Brick(Cube m_model) : m_model(std::move(m_model)) {}

void Brick::disable() { m_isActive = false; }

void Brick::enable() { m_isActive = true; }

void Brick::setSize(glm::vec3 size) {
  m_size = size;
  updateModel();
}

void Brick::reset() {
  m_durability = m_maxDurability;
  m_isActive = m_isActiveDefaultState;
}
