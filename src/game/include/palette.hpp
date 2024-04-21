#ifndef PALETTE_HPP_
#define PALETTE_HPP_

#include "brick.hpp"
class Pallette : public Brick {

public:
  Pallette(const Pallette &) = delete;
  Pallette(Pallette &&) = default;
  Pallette &operator=(const Pallette &) = delete;
  Pallette &operator=(Pallette &&) = default;

  Pallette() {
    setSize({0.3f, 0.08f, 1.f});
    setPositionOrigin({0.f, -1.f + getModel().getScale().y / 2, 0.f});
  }
};

#endif // PALETTE_HPP_
