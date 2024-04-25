#ifndef PALETTE_HPP_
#define PALETTE_HPP_

#include "brick.hpp"
class Pallette : public Cube {

public:
  Pallette(const Pallette &) = delete;
  Pallette(Pallette &&) = default;
  Pallette &operator=(const Pallette &) = delete;
  Pallette &operator=(Pallette &&) = default;

  Pallette() {
    setScale({0.3f, 0.08f, 1.f});
    setPosition({0.f, -1.f + getScale().y / 2, 0.f});
  }
};

#endif // PALETTE_HPP_
