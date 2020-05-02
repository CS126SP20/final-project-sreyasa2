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

Engine::Engine(size_t size_input)
 : car(GetCarLocation()),
   obstacle(GetObjectLocation()),
   coin(GetObjectLocation()),
   next_direction(Direction::left) {
  size = size_input;
}

Location Engine::GetObjectLocation() {
  int rand_lane = GetRandomLane();
  occupied_lanes.push_back(rand_lane);
  return lanes[rand_lane];
}

Location Engine::GetCarLocation() { 
  return Location(lanes[0].Row(), 600); 
}

int Engine::GetRandomLane() const {
  int rand_loc = ci::randInt(0, 3);
  for (int i = 0; i < occupied_lanes.size(); i++) {
    if (rand_loc == occupied_lanes[i]) {
      rand_loc = ci::randInt(0, 3);
      i = 0;
    }
  }
  return rand_loc;
}
}  // namespace mylibrary
