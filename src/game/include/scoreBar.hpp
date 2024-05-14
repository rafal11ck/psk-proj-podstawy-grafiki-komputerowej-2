#ifndef SCOREBAR_HPP_
#define SCOREBAR_HPP_

#include "drawable.hpp"

class ScoreBar : public Drawable {
  long m_score{};

public:
  ScoreBar() = default;
  ScoreBar(const ScoreBar &) = delete;
  ScoreBar(ScoreBar &&) = default;
  ScoreBar &operator=(const ScoreBar &) = delete;
  ScoreBar &operator=(ScoreBar &&) = default;

  void draw(Shader &shader) override;
  void addScore(long points);

  ~ScoreBar() = default;
};

#endif // SCOREBAR_HPP_
