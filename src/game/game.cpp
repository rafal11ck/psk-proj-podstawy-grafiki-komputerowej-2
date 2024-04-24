#include "game.hpp"
#include "log.hpp"

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

  glm::vec3 posChange{m_ballSpeed * glm::vec3{m_ballMovementVector}};
  m_ball->setPosition(m_ball->getPosition() + posChange);
  handleCollisions();

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

std::ostream &operator<<(std::ostream &os, glm::vec3 vec) {
  os << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
  return os;
}

void Game::handleBrickCollisions() {
  auto hitBrick{m_gameLevel->findCollidingBrick(*m_ball.get())};

  // if collides
  if (hitBrick.first.has_value()) {
    // brick
    auto &brick{hitBrick.first.value()};
    // point
    auto &collisonPoint{hitBrick.second};

    LOGINFO << "HIT at " << collisonPoint << '\n';
    auto ballToCollisonPointVec{collisonPoint - m_ball->getPosition()};
    Game::performBallReflect(glm::normalize(ballToCollisonPointVec));

    // normalize Vector so it's lentght is 1,
    // then extend to size of ball radius.
    // This is relative positon from ball to coliision point.
    auto revertVec{m_ball->getRadius() *
                   glm::normalize(ballToCollisonPointVec)};

    // Move ball back as if it bounced off instead of penetrating.
    auto newBallPos{collisonPoint - revertVec};

    // damage the brick
    brick.get().damage();
    brick.get().disableIfHasNoDurability();
  }
};

void Game::setBallMovementVector(glm::vec3 vector) {
  m_ballMovementVector = vector;
};

void Game::setBallSpeed(float speed) { m_ballSpeed = speed; };
