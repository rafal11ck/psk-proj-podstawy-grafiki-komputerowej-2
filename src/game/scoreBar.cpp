

#include "scoreBar.hpp"
#include "engine.hpp"

#define GLT_IMPLEMENTATION
#include "gltext.h"

#include <format>

void ScoreBar::addScore(long points) { m_score += points; }

void ScoreBar::draw(Shader &shader) {
  gltInit();
  GLTtext *text = gltCreateText();
  gltBeginDraw();
  std::string score{"score: " + std::to_string(m_score)};

  gltSetText(text, score.c_str());
  // YES hardcoded color
  gltColor(1.0f, 1.0f, 1.0f, 1.0f);
  auto size{Engine::getInstance().getWindow().getSize()};
  // Yes hardcodec postion
  gltDrawText2DAligned(text, 3 * (size.x / 100.0), size.y / 2, 3, GLT_LEFT,
                       GLT_TOP);

  gltDeleteText(text);
  gltEndDraw();
  gltTerminate();
};
