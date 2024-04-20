#include "brick.hpp"
#include <log.hpp>

void Brick::draw(Shader &shader) {
  LOGINFO << "draw";

  m_model.draw(shader);
}

Brick::Brick() { std::cout << "Cor"; };
Shape &Brick::getModel() { return m_model; };
