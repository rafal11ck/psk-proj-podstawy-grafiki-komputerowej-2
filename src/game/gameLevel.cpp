#include "gameLevel.hpp"
#include "log.hpp"

float GameLevel::s_borderPaddingSide{0.1};
float GameLevel::s_borderPaddingTop{0.15};
float GameLevel::s_brickHeight{1};

int GameLevel::s_columnCount{10};
int GameLevel::s_rowCount{3};

float GameLevel::brickWidth() const {
  return (2.0f - 2 * s_borderPaddingSide) / s_columnCount;
}

float GameLevel::bricksVericalScreenSpace() const {
  return 1.f - s_borderPaddingTop - (1.f - s_brickHeight);
}

float GameLevel::brickHeight() const {
  return bricksVericalScreenSpace() / s_rowCount;
}

void GameLevel::scaleBricks() {
  for (auto &bricks : m_bricks) {
    for (auto &brick : bricks) {
      brick.getModel().setScale(brickWidth() / 2, brickHeight() / 2, 1.f);
    }
  }
};

GameLevel::~GameLevel(){};

void GameLevel::draw(Shader &shader) {
  for (auto &brickRow : m_bricks) {
    {
      for (auto &brick : brickRow) {
        brick.draw(shader);
      }
    }
  }
};

GameLevel::GameLevel(int rowCount, int columnCount)
    : m_rowCount(rowCount), m_columnCount(columnCount) {
  LOGTRACEN;
  m_bricks.resize(m_rowCount);
  for (std::vector<Brick> &row : m_bricks) {
    LOGINFO << "Intiaializing row\n";
    row.resize(columnCount);
    for (Brick &brick : row) {
      brick = Brick{};
    }
  }
  scaleBricks();
  setPostions();
}

void GameLevel::setPostions() {
  const float startX{-1.f + s_borderPaddingSide + brickWidth() / 2.f};
  const float startY{1.f - s_borderPaddingTop - brickHeight() / 2.f};
  float curY{startY};
  for (auto &row : m_bricks) {

    float currentX{startX};
    for (Brick &brick : row) {
      LOGINFO << "Setting brick pos: " << &brick.getModel() << " to "
              << currentX << '\n';
      brick.getModel().setPosition(currentX, curY, 0.f);
      currentX += brickWidth();
    }
    curY -= brickHeight();
  }
}
