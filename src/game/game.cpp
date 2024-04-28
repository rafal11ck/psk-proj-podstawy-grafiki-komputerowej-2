#include "game.hpp"
#include "log.hpp"

Game::Game(std::shared_ptr<Ball> ball) : m_ball(ball) {
  m_palette.setScale(0.2, 0.05, 1.f);
  m_palette.setPosition({0.f, -1.f + m_palette.getScale().y, 0.f});
};

void Game::draw(Shader &shader) {
  m_ball->draw(shader);
  m_gameLevel->draw(shader);
  m_palette.draw(shader);
};
void Game::update(const float dt) {
  processBallMovement(dt);
  processPalleteMovement(dt);
};

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

  glm::vec3 posChange{m_ballMovementSpeed * glm::vec3{m_ballMovementVector}};
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
  m_ballMovementVector = glm::normalize(vector);
};

void Game::setBallSpeed(float speed) { m_ballMovementSpeed = speed; };

std::optional<glm::vec3> Game::getPalleteMovmentVector() const {
  glm::vec3 vector{};
  bool doesMove{false};

  auto handleMovement{
      [&](MovementDirection direction1, MovementDirection direction2) {
        // if neither or both are moving cancel out.
        if (isPalleteMoving(direction1) == isPalleteMoving(direction2)) {
          return;
        }

        vector = vector + (isPalleteMoving(direction1) ? getVector(direction1)
                                                       : getVector(direction2));
        doesMove = true;
      }};

  handleMovement(MovementDirection::front, MovementDirection::back);
  handleMovement(MovementDirection::left, MovementDirection::right);

  if (doesMove)
    return glm::normalize(vector);
  else
    return std::nullopt;
}

bool Game::isPalleteMoving(MovementDirection direction) const {
  return m_palleteMoves[static_cast<ssize_t>(direction)];
}

void Game::setPalleteMovementState(MovementDirection movementDirection,
                                   bool state) {
  assert(movementDirection < MovementDirection::max_movementDirection);

  m_palleteMoves[static_cast<ssize_t>(movementDirection)] = state;
}

void Game::processPalleteMovement(float dt) {
  auto palleteMovementVec{getPalleteMovmentVector()};
  // if does not move ignore.
  if (!palleteMovementVec.has_value()) {
    return;
  }

  LOGINFO << "Moving pallete by " << palleteMovementVec.value() << "\n";
  auto moveVec{m_palletteMovementSpeed * dt * palleteMovementVec.value()};
  auto postion{m_palette.getPosition() + moveVec};
  postion = glm::clamp(
      postion,
      {m_gameLevel->getCollisonLinePositonLeft() + m_palette.getScale().x,
       -1.f + m_palette.getScale().y, -1.f + m_palette.getScale().z},
      {m_gameLevel->getCollisionLinePositionRight() - m_palette.getScale().x,
       -1.f + m_palette.getScale().y, 1.f - m_palette.getScale().z});

  m_palette.setPosition(postion);
}

void Game::handlePalleteCollisons() { Pallette &pallete{m_palette}; }
