#include "engine.hpp"
#include "game.hpp"
#include "log.hpp"
#include <filesystem>
#include <memory>
#include <random>

Engine &engine{Engine::getInstance()};

auto ball{std::make_shared<Ball>()};
auto game{std::make_unique<Game>(ball)};

void cameraContorolSwap();
void keyEventHandler(const Engine::Event &event);
void loopFun();

void changeDirToExecutableParentDir(std::string execFilePath) {
  std::filesystem::path mainFilePath(execFilePath);
  std::filesystem::current_path(mainFilePath.parent_path());
  FileSystem::setResourcesPath(std::filesystem::current_path().string() +
                               "/resources/");

  LOGINFO << "Working dir = " << std::filesystem::current_path() << '\n';
}

int main(int argc, char *argv[]) {
  changeDirToExecutableParentDir(argv[0]);

  // Initialzie game
  auto gl{std::make_unique<GameLevel>(3, 10)};
  gl->setBricksHeight(0.1f);
  game->setGameLevel(std::move(gl));
  engine.addDrawable(game.get());
  engine.addLight(ball.get());

  // Loop function
  engine.setLoopFunction(loopFun);

  // Events
  engine.setEventHandler(Engine::Event::KeyPressed, keyEventHandler);

  engine.setClearColor(glm::vec4{0, 0, 0, 1});
  engine.setProjectionType(Engine::ProjectionType::perspective);

  // move camera back initially
  engine.getCamera().processKeyboard(Camera::BACKWARD, 1.2);

  engine.loop();
}

void loopFun() {
  game->processBallMovement(engine.getLastFrameDuration().asSeconds());
  static float dt{};
  dt += engine.getLastFrameDuration().asSeconds();

  if (dt > 2.5) {
    ball->setPosition(0.0f, 0.35f, 0.f);

    static std::mt19937 generator{};

    static std::uniform_real_distribution dis{-1.f, 1.f};

    float x{dis(generator)};
    float y{1.f + dis(generator)};

    game->setBallMovementVector(glm::normalize(glm::vec3{x, y, 0.f}));
    dt = 0;
    game->setBallSpeed(0.02);
  }
}

void keyEventHandler(const Engine::Event &event) {
  switch (event.key.code) {
  case sf::Keyboard::M:
    static bool modeWire{};
    engine.setWireframeMode(modeWire = !modeWire);
    return;
  case sf::Keyboard::N:
    static bool modeCam{};
    modeCam = !modeCam;
    engine.setProjectionType(modeCam ? Engine::ProjectionType::orthogonal
                                     : Engine::ProjectionType::perspective);
    return;
  case sf::Keyboard::K:
    //   cameraContorolSwap();
  default:
    return;
  }
}
