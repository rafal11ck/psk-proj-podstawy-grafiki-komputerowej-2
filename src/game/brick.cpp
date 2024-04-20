#include "brick.hpp"
#include <log.hpp>

void Brick::draw(Shader &shader) {
  LOGINFO << "draw";

  m_model.draw(shader);
}

Brick::Brick() { LOGTRACEN; };

Shape &Brick::getModel() { return m_model; };

Brick::~Brick(){};
