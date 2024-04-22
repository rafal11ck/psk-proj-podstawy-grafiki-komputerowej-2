#include "game.hpp"
#include "log.hpp"

Game::Game(std::shared_ptr<Ball> ball) : m_ball(ball){};

void Game::draw(Shader &shader) {
  m_ball->draw(shader);
  m_gameLevel->draw(shader);
  m_pallette.draw(shader);
};
void Game::update(const float dt) { processBallMovement(dt); };

void Game::processBallMovement(const float dt) {
  glm::vec3 collisonNvec{findBallCollisonVector()};
  // if collison occured
  if (glm::length(collisonNvec) > 0) {
    performBallReflect(collisonNvec);
  }

  glm::vec3 posChange{m_ballspeed * glm::vec3{m_ballMovementVector}};
  m_ball->setPosition(m_ball->getPosition() + posChange);

  LOGINFO << m_ball->getPosition().x << '\n';
};

glm::vec3 Game::findBallCollisonVector() const {
  // Map border collsion right
  if (doesBallCollideBorderRight()) {
    return {-1.f, 0.f, 0.f};
  }

  // Map border collsion left
  if (doesBallCollideBorderLeft()) {
    return {1.f, 0.f, 0.f};
  }

  // Map border collsion top
  if (doesBallCollideBorderTop()) {
    return {0.f, -1.f, 0.f};
  }

  return {0.f, 0.f, 0.f};
};
