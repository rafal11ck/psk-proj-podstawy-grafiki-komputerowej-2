#include "engine.hpp"
#include "game.hpp"
#include "log.hpp"
#include <filesystem>
#include <memory>

#define GLT_IMPLEMENTATION
#include "gltext.h"

Engine &engine{Engine::getInstance()};

void keyPressedEventHandler(const Engine::Event &event);
void keyReleasedEventHandler(const Engine::Event &event);

void loopFun();
void changeDirToExecutableParentDir(std::string execFilePath);
void gameOverCheckAndHandle();
void gameResetOnSpaceText();
void gameReset(std::weak_ptr<Game> ptr);

auto ball{std::make_shared<Ball>()};
auto game{std::make_shared<Game>(ball)};

int main(int argc, char *argv[]) {
  changeDirToExecutableParentDir(argv[0]);

  // Initialzie game
  auto gl{std::make_unique<GameLevel>(6, 10)};
  gl->setBricksHeight(0.1f);
  game->setGameLevel(std::move(gl));

  engine.addDrawable(game.get());
  engine.addLight(ball.get());

  // game->setBallMovementVector({0, -1.f, 0});
  // game->setBallSpeed(0.03);
  ball->setScale(0.75);

  // Add light
  auto light{std::make_unique<Light>()};
  light->setAmbient(0.2f, 0.2f, 0.2f);
  engine.addLight(light.get());

  // Loop function
  engine.setLoopFunction(loopFun);

  // Events
  engine.setEventHandler(Engine::Event::KeyPressed, keyPressedEventHandler);
  engine.setEventHandler(Engine::Event::KeyReleased, keyReleasedEventHandler);

  engine.setClearColor(glm::vec4{0, 0, 0, 1});
  engine.setProjectionType(Engine::ProjectionType::perspective);

  // move camera back initially
  engine.getCamera().processKeyboard(Camera::BACKWARD, 1.4);

  engine.loop();
}

void changeDirToExecutableParentDir(std::string execFilePath) {
  std::filesystem::path mainFilePath(execFilePath);
  std::filesystem::current_path(mainFilePath.parent_path());
  FileSystem::setResourcesPath(std::filesystem::current_path().string() +
                               "/resources/");

  LOGINFO << "Working dir = " << std::filesystem::current_path() << '\n';
}

void loopFun() {
  game->update(engine.getLastFrameDuration().asSeconds());
  // if reset is thing that should happen next
  if (game->isGameOver()) {
    // display text
    gameResetOnSpaceText();
  }

  static float dt{};
}

void keyPressedEventHandler(const Engine::Event &event) {
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
  case sf::Keyboard::W:
    game->setPalleteMovementState(Game::MovementDirection::back, true);
    return;
  case sf::Keyboard::S:
    game->setPalleteMovementState(Game::MovementDirection::front, true);
    return;
  case sf::Keyboard::A:
    game->setPalleteMovementState(Game::MovementDirection::left, true);
    return;
  case sf::Keyboard::D:
    game->setPalleteMovementState(Game::MovementDirection::right, true);
    return;
    // on space reset game
  case sf::Keyboard::Space:
    gameReset(game);
    return;
  default:
    return;
  }
}

void keyReleasedEventHandler(const Engine::Event &event) {
  switch (event.key.code) {

  case sf::Keyboard::W:
    game->setPalleteMovementState(Game::MovementDirection::back, false);
    return;
  case sf::Keyboard::S:
    game->setPalleteMovementState(Game::MovementDirection::front, false);
    return;
  case sf::Keyboard::A:
    game->setPalleteMovementState(Game::MovementDirection::left, false);
    return;
  case sf::Keyboard::D:
    game->setPalleteMovementState(Game::MovementDirection::right, false);
    return;
  default:
    break;
  }
}

void gameResetOnSpaceText() {
  gltInit();
  GLTtext *text = gltCreateText();
  gltBeginDraw();
  std::string score{"PRESS SPACE TO RESTART"};

  gltSetText(text, score.c_str());
  // YES hardcoded color
  gltColor(1.0f, 1.0f, 1.0f, 1.0f);
  auto size{Engine::getInstance().getWindow().getSize()};
  // Yes hardcoded postion
  gltDrawText2DAligned(text, size.x / 2.0, size.y / 2.0, 3, GLT_CENTER,
                       GLT_CENTER);

  gltDeleteText(text);
  gltEndDraw();
  gltTerminate();
};

void gameReset(std::weak_ptr<Game> ptr) {
  auto game{ptr.lock()};
  // Only reset game if it's game over
  if (game->isGameOver())
    game->reset();
}
