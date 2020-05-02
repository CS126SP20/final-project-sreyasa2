//
// Created by sreya on 4/23/2020.
//

#include "mylibrary/engine.h"
#include "mylibrary/location.h"
#include <cstdlib>
#include <set>
#include <stdexcept>
#include "cinder/Rand.h"

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

Engine::Engine(const size_t size_input)
 : car(GetCarLocation()),
   obstacle(lanes[1]),
   coin(lanes[0]),
   next_direction(Direction::left) {
     size = size_input;
     occupied_lanes = {};
}

Location Engine::GetObjectLocation() {
  int rand_lane = GetRandomLane();
  Location location(lanes[rand_lane]);
  occupied_lanes.push_back(location);
  return lanes.at(rand_lane);
}

Location Engine::GetCarLocation() { 
  return lanes[0]; 
}

int Engine::GetRandomLane() const {
  int rand_loc = ci::randInt(0, 4);
  if (occupied_lanes.empty()) {
    return rand_loc;
  }
  auto i = std::find(occupied_lanes.begin(), occupied_lanes.end(), lanes.at(rand_loc));
  while (i != occupied_lanes.end()) {
    rand_loc = ci::randInt(0, 4);
    i = std::find(occupied_lanes.begin(), occupied_lanes.end(), lanes.at(rand_loc));
  }
  return rand_loc;
}

Car Engine::GetCar() const { return car; }
}  // namespace mylibrary
