#ifndef PALETTE_HPP_
#define PALETTE_HPP_

#include "cube.hpp"

class Pallette : public Cube {

public:
  Pallette(const Pallette &) = delete;
  Pallette(Pallette &&) = default;
  Pallette &operator=(const Pallette &) = delete;
  Pallette &operator=(Pallette &&) = default;

  Pallette() {}
};

#endif // PALETTE_HPP_
