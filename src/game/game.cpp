#include "game.hpp"

Game::Game(std::shared_ptr<Ball> ball) : m_ball(ball){};

void Game::draw(Shader &shader) {
  m_ball->draw(shader);
  m_gameLevel->draw(shader);
  m_palette.draw(shader);
};
void Game::update(const float dt) { processBallMovement(dt); };

glm::vec3 Game::mapBordersCollision() const {
  // Map border collsion right
  if (m_ball->getPosition().x + m_ball->getRadius() >=
          m_gameLevel->getCollisionLinePositionRight()) {
    return {-1.f, 0.f, 0.f};
  }

  // Map border collsion left
  if (m_ball->getPosition().x - m_ball->getRadius() <=
      m_gameLevel->getCollisonLinePositonLeft()) {
    return {1.f, 0.f, 0.f};
  };

  // Map border collsion top
  if (m_ball->getPosition().y + m_ball->getRadius() >=
      m_gameLevel->getCollisonLinePositonTop()) {
    return {0.f, -1.f, 0.f};
  }

  return {0.f, 0.f, 0.f};
}

void Game::processBallMovement(const float dt) {

  handleCollisions();

  glm::vec3 posChange{m_ballSpeed * glm::vec3{m_ballMovementVector}};
  m_ball->setPosition(m_ball->getPosition() + posChange);

  // LOGINFO << m_ball->getPosition().x << '\n';
};

void Game::handleCollisions() {
  // Handle border collison.
  auto borderColVec{mapBordersCollision()};
  if (glm::length(borderColVec) > 0) {
    performBallReflect(borderColVec);
    return;
  }

    handleBrickCollisions();

  /// @TODO Handle pallete collision.
}

/// @TODO Handle brick collisons.
void Game::handleBrickCollisions() {
  auto hitBrick{m_gameLevel->findCollidingBrick(*m_ball.get())};
};
