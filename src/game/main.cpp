#include "engine.hpp"
#include "game.hpp"
#include <memory>

Engine &engine{Engine::getInstance()};

void setupEngine() {
  Light *light{new Light{}};
  light->setAmbient(glm::vec3{0.2f, 0.2f, 0.2f});
  // light->setDiffuse(.4f, .4f, .4f);
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
}

int main() {
  setupEngine();

  auto ball{std::make_shared<Ball>()};
  auto game{std::make_unique<Game>(ball)};
  engine.addDrawable(game.get());
  engine.addLight(ball.get());

  ball->setPosition(0.5f, .3f, .0f);

  engine.setLoopFunction([&]() {
    constexpr float rotTime{3};
    static sf::Clock clock{};
    if (clock.getElapsedTime().asSeconds() > rotTime) {
      clock.restart();
    };
    float xPos{-1.f + (clock.getElapsedTime().asSeconds() / rotTime) * 2};
    ball->setPosition(xPos, 0.f, 0.f);
  });

  engine.getCamera().processKeyboard(Camera::BACKWARD, 2);

  engine.loop();
}
