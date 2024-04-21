#include "game.hpp"

Game::Game(std::shared_ptr<Ball> ball) : m_ball(ball){};

void Game::draw(Shader &shader) {
  m_ball->draw(shader);
  m_gameLevel->draw(shader);
};
