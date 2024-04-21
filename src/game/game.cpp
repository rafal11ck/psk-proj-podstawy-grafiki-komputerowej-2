#include "game.hpp"

Game::Game(){};

void Game::draw(Shader &shader) {
  m_ball.draw(shader);
  m_gameLevel.get()->draw(shader);
};
