#include "collisions.hpp"
#include "ball.hpp"
#include <glm/fwd.hpp>
#include <optional>

std::optional<glm::vec3> Collisiosns::findCollisonPoint(const Ball *ball,
                                                        const Cube *cube) {
  const glm::vec3 brickHalfExtent{cube->getScale()};

  auto diffVector{ball->getPosition() - cube->getPosition()};
  // Raw distance from brick origin to ball origin.
  const float rawDistance{glm::length(diffVector)};
  // Farest raw distance of ball-brick origins for collision to be
  // possible.
  float checkingRange{glm::length(brickHalfExtent) + ball->getRadius()};
  // Skip if not within checking range
  if (rawDistance > checkingRange)
    return {};

  auto nearestPoint{findNearestPointOnContour(ball, cube)};

  float distance{glm::distance(nearestPoint, ball->getPosition())};

  // If collision occurs
  if (distance <= ball->getRadius()) {
    // return point.
    return nearestPoint;
  }

  return {};
}

glm::vec3 Collisiosns::findNearestPointOnContour(const Ball *ball,
                                                 const Cube *cube) {
  assert(ball != nullptr);
  assert(cube != nullptr);
  const glm::vec3 brickHalfExtent{cube->getScale()};

  auto diffVector{ball->getPosition() - cube->getPosition()};
  // Where is the closest point to the ball that is on the brick's surface
  glm::vec3 clamped{glm::clamp(diffVector, -brickHalfExtent, brickHalfExtent)};

  // Position of nearest point to the ball on the brick's surface.
  glm::vec3 nearestPoint{cube->getPosition() + clamped};

  return nearestPoint;
};
