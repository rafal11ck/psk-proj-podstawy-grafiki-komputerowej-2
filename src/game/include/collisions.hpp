#ifndef COLLISIONS_HPP_
#define COLLISIONS_HPP_

#include "ball.hpp"
#include "cube.hpp"
#include <optional>

class Collisiosns {
public:
  /**
   * @brief Find point of clllioson if such exists.
   */
  static std::optional<glm::vec3> findCollisonPoint(const Ball *ball,
                                                    const Cube *cube);

  static glm::vec3 findNearestPointOnContour(const Ball *ball,
                                             const Cube *cube);
};

#endif // COLLISIONS_HPP_
