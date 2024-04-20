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
  scaleBricks();
  setPostions();
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

void GameLevel::scaleBricks() {
  int row{};
  for (auto &brickRow : m_bricks) {
    int col{};
    {
      for (auto &brick : brickRow) {
        brick.getModel().setScale(getBrickWidth() / 2, getBrickHeight() / 2,
                                  1.f);
        ++col;
      }
    }
    ++row;
  }
};

void GameLevel::setPostions() {
  int row{};
  for (auto &brickRow : m_bricks) {
    int col{};
    {
      for (auto &brick : brickRow) {
        const auto pos{computeBrickPositionOrigin(col, row)};
        LOGINFO << "COL : " << col << " ROW" << row << " -> POS is ("
                << pos.first << ", " << pos.second << ")" << '\n';
        brick.getModel().setPosition(pos.first, pos.second, 0.0f);
        ++col;
      }
    }
    ++row;
  }
}
