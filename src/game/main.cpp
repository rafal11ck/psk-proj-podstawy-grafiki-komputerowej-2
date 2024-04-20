#include "engine.hpp"
#include <iostream>

Engine &engine{Engine::getInstance()};

int main() {
  std::cout << "Hi";

  engine.loop();
}
