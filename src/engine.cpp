//
// Created by sreya on 4/23/2020.
//

#include "mylibrary/engine.h"
#include "mylibrary/location.h"
#include <cstdlib>
#include <set>
#include <stdexcept>

namespace mylibrary {

Location FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::left:
      return {0, -1};
    case Direction::right:
      return {0, +1};
  }

  throw std::out_of_range("switch statement not matched");
}
//Engine::Engine() {}
//Engine::Engine(unsigned seed) {}
}  // namespace mylibrary
