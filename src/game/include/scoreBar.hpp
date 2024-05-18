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

  /**
   * @brief Add score.
   * @param points Ammount of poitnts to add.
   */
  void addScore(long points);

  /**
   * @brief Reset score counter.
   */
  void reset();

  ~ScoreBar() = default;
};

#endif // SCOREBAR_HPP_
