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
  processBallCollisons();

  glm::vec3 posChange{m_ballspeed * glm::vec3{m_ballMovementVector, 0.f}};
  m_ball->setPosition(m_ball->getPosition() + posChange);

  LOGINFO << m_ball->getPosition().x << '\n';
};

void Game::processBallCollisons() {
  if (doesBallCollideBorderRight() || doesBallCollideBorderLeft()) {
    m_ballMovementVector = ballVectorAfterWallCollision(BallCollison::vertical);
  }
};

glm::vec2 Game::ballVectorAfterWallCollision(BallCollison collisonDirection) {
  glm::vec2 vec{m_ballMovementVector};
  switch (collisonDirection) {
  case BallCollison::horizontal:
    vec.y = -vec.y;
    break;
  case BallCollison::vertical:
    vec.x = -vec.x;
    break;
  }
  return glm::normalize(vec);
};
