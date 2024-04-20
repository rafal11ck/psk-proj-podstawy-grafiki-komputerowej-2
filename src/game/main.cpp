#include "engine.hpp"
#include "gameLevel.hpp"
#include "include/brick.hpp"
#include <memory>

Engine &engine{Engine::getInstance()};

int main() {
  Light *light{new Light{}};
  light->setAmbient(glm::vec3{0.4f, 0.4f, 0.4f});
  light->setDiffuse(.4f, .4f, .4f);
  engine.addLight(light);

  auto glevel{std::make_unique<GameLevel>(GameLevel{})};
  engine.addDrawable(glevel.get());

  engine.setWireframeMode(true);
  engine.setCameraHandlingKeyboard(true);
  // engine.setProjectionType(Engine::ProjectionType::perspective);
  engine.getCamera().processKeyboard(Camera::BACKWARD, 2);

  engine.loop();
}
