#include "engine.hpp"
#include "game.hpp"
#include <memory>

Engine &engine{Engine::getInstance()};

bool state{false};

void cameraContorolSwap() {
  state = !state;
  engine.setCameraHandlingKeyboard(state);
  engine.setCameraHandlingMouse(state);
  engine.getWindow().setMouseCursorGrabbed(state);
  engine.getWindow().setMouseCursorVisible(!state);
}

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
        case sf::Keyboard::K:
          cameraContorolSwap();
        default:
          return;
        }
      });

  engine.setProjectionType(Engine::ProjectionType::perspective);
}

int main() {
  setupEngine();

  auto ball{std::make_shared<Ball>()};

  auto gl{std::make_unique<GameLevel>(1, 1)};
  gl->setBricksHeight(0.035f);

  auto game{std::make_unique<Game>(ball)};
  game->setGameLevel(std::move(gl));

  engine.addDrawable(game.get());
  engine.addLight(ball.get());

  ball->setPosition(0.5f, .7f, .0f);

  engine.setLoopFunction([&]() {
    game->processBallMovement(engine.getLastFrameDuration().asSeconds());
    if (state) {
      engine.moveMouseToCenterOfWindow();
    }
  });

  engine.getCamera().processKeyboard(Camera::BACKWARD, 1.2);

  engine.loop();
}
