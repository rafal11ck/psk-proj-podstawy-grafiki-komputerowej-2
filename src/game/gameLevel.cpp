#include "gameLevel.hpp"
#include <log.hpp>

std::pair<float, float> GameLevel::computeBrickPositionOrigin(int column,
                                                              int row) const {
  const std::pair bricksStartingPosition{getBricksStartingPostion()};
  // First brick origin.
  float x{bricksStartingPosition.first + getBrickWidth() / 2};
  float y{bricksStartingPosition.second - getBrickHeight() / 2};

  // Compute offsets
  float xoffset{getBrickWidth()};
  float yoffset{getBrickHeight()};

  // Final cordinates
  float effectiveX{x + xoffset * column};
  float effectiveY{y - yoffset * row};

  return {effectiveX, effectiveY};
}

std::pair<float, float> GameLevel::getBricksStartingPostion() const {
  constexpr std::pair<float, float> topLeftCornerPos{-1.f, 1.f};
  float x{topLeftCornerPos.first};
  float y{topLeftCornerPos.second};
  y -= m_paddingBricksTop;
  float xPaddings{2.f - getBricksHorizontalSpace()};
  x -= xPaddings / 2;
  return {x, y};
}

float GameLevel::getBricksHorizontalSpace() const {
  return 2.f - 2 * m_paddingBricksSide;
}

float GameLevel::getBrickWidth() const {
  return getBricksHorizontalSpace() / m_bricksColumnCount;
}
GameLevel::GameLevel(int rowCount, int columnCount)
    : m_bricksRowCount(rowCount), m_bricksColumnCount(columnCount) {
  m_bricks.resize(m_bricksRowCount);
  for (auto &row : m_bricks) {
    row.resize(columnCount);
  }
  setBrickSizes();
  setBrickPostions();
};

float GameLevel::getBrickHeight() const { return m_brickHeight; }

GameLevel::~GameLevel() = default;

void GameLevel::draw(Shader &shader) {
  for (auto &brickRow : m_bricks) {
    {
      for (auto &brick : brickRow) {
        brick.draw(shader);
      }
    }
  }
};

void GameLevel::setBrickSizes() {
  int row{};
  for (auto &brickRow : m_bricks) {
    int col{};
    {
      for (auto &brick : brickRow) {
        ++col;
        brick.setSize({getBrickWidth(), getBrickHeight(), 1.f});
      }
    }
    ++row;
  }
};

void GameLevel::setBrickPostions() {
  int row{};
  for (auto &brickRow : m_bricks) {
    int col{};
    {
      for (auto &brick : brickRow) {
        const auto pos{computeBrickPositionOrigin(col, row)};
        LOGINFO << "COL : " << col << " ROW" << row << " -> POS is ("
                << pos.first << ", " << pos.second << ")" << '\n';
        brick.setPositionOrigin({pos.first, pos.second, 0.f});
        ++col;
      }
    }
    ++row;
  }
}
void GameLevel::setBricksHeight(float height) {
  m_brickHeight = height;
  updateBricks();
}

void GameLevel::updateBricks() {
  setBrickSizes();
  setBrickPostions();
}

float GameLevel::getCollisonLinePositonLeft() const {
  // Beacuse middle is on 0 left border is just `-right`.
  return -getCollisionLinePositionRight();
};

float GameLevel::getCollisionLinePositionRight() const {
  return (getBricksHorizontalSpace() / 2);
};

std::optional<glm::vec3> findCollisonPoint(Ball &ball, Brick &brick) {

  const glm::vec3 brickHalfExtent{0.5f * brick.getSize()};

  auto diffVector{ball.getPosition() - brick.getPositonOrigin()};
  // Raw distance from brick origin to ball origin.
  const float rawDistance{glm::length(diffVector)};
  // Farest raw distance of ball-brick origins for collision to be
  // possible.
  float checkingRange{glm::length(brickHalfExtent) + ball.getRadius()};
  // Skip if not within checking range
  if (rawDistance > checkingRange)
    return {};

  // Where is the closest point to the ball that is on the brick's surface
  glm::vec3 clamped{glm::clamp(diffVector, -brickHalfExtent, brickHalfExtent)};

  // Position of nearest point to the ball on the brick's surface.
  glm::vec3 nearestPoint{brick.getPositonOrigin() + clamped};

  float distance{glm::distance(nearestPoint, ball.getPosition())};

  // If collision occurs
  if (distance <= ball.getRadius()) {
    return nearestPoint;
  }

  return {};
}

const std::pair<std::optional<std::reference_wrapper<Brick>>, glm::vec3>
GameLevel::findCollidingBrick(const Ball &ball) {
  auto result{std::optional<std::reference_wrapper<Brick>>()};
  glm::vec3 collisonPoint{};
  float smallestDistanceSoFar{INFINITY};

  // For each brick
  for (auto &brickRow : m_bricks) {
    for (Brick &brick : brickRow) {

      // @FIXME
      // @TODO
      // auto disPoint;
      if (smallestDistanceSoFar > distance) {
        smallestDistanceSoFar = distance;
        result = brick;
        collisonPoint = nearestPoint;
      }
    }
  }
}
return {result, collisonPoint};
}
