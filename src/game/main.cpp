#include "engine.hpp"
#include "game.hpp"
#include <memory>

Engine &engine{Engine::getInstance()};

void setupEngine() {
  Light *light{new Light{}};
  light->setAmbient(glm::vec3{0.4f, 0.4f, 0.4f});
  light->setDiffuse(.4f, .4f, .4f);
  engine.addLight(light);

  engine.setWireframeMode(true);

  engine.setEventHandler(
      Engine::Event::KeyPressed, [&](const sf::Event &event) {
        switch (event.key.code) {
        case sf::Keyboard::M:
          static bool modeWire{};
          engine.setWireframeMode(modeWire = !modeWire);
          return;
        case sf::Keyboard::N:
          static bool modeCam{};
          modeCam = !modeCam;
          engine.setProjectionType(modeCam
                                       ? Engine::ProjectionType::orthogonal
                                       : Engine::ProjectionType::perspective);
          return;
        default:
          return;
        }
      });

  engine.setCameraHandlingKeyboard(true);
  // engine.setCameraHandlingMouse(true);
  // engine.getWindow().setMouseCursorGrabbed(true);
  // engine.getWindow().setMouseCursorVisible(false);
  engine.setProjectionType(Engine::ProjectionType::perspective);

  engine.setLoopFunction([&]() { // engine.moveMouseToCenterOfWindow();
  });
}

int main() {
  setupEngine();

  auto game{std::make_unique<Game>()};
  engine.addDrawable(game.get());

  engine.getCamera().processKeyboard(Camera::BACKWARD, 2);

  engine.loop();
}
