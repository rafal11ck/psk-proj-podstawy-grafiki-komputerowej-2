#include "engine.hpp"
#include "gameLevel.hpp"
#include "include/brick.hpp"
#include <memory>

Engine &engine{Engine::getInstance()};

int main() {
  Light *light{new Light{}};
  light->setAmbient(glm::vec3{0.2});
  light->setDiffuse(0.3, 0.3, 0.3);
  engine.addLight(light);

  auto gameLevel{std::make_unique<GameLevel>()};
  gameLevel.get()->scaleBricks();
  // engine.addDrawable(gameLevel.get());

  engine.loop();
}
