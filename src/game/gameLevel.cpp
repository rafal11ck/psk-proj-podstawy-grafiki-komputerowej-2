#include "gameLevel.hpp"

float GameLevel::s_borderPaddingSide{0.1};
float GameLevel::s_borderPaddingTop{0.1};
float GameLevel::s_bricksScreenSpaceHeight{0.3};

int GameLevel::s_columnCount{10};
int GameLevel::s_rowCount{3};

float GameLevel::brickWidth() const {
  return (1.0f - 2 * s_borderPaddingSide) / s_columnCount;
}

float GameLevel::bricksVericalScreenSpace() const {
  return 1.f - s_borderPaddingTop - (1.f - s_bricksScreenSpaceHeight);
}

float GameLevel::brickHeight() const {
  return bricksVericalScreenSpace() / s_rowCount;
}
void GameLevel::scaleBricks() {
  for (auto &bricks : m_bricks) {
    for (auto &brick : bricks) {
      brick.getModel().setScale(brickWidth(), brickHeight(), 1.f);
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

GameLevel::GameLevel(int rowCount, int columnCount) {
  m_bricks.resize(rowCount);
  for (auto &row : m_bricks) {
    row.reserve(columnCount);
    for (int i{}; i < columnCount; ++i) {
      // row.emplace_back(Brick{});
    }
  }
}
