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
      return {0, -30};
    case Direction::right:
      return {0, +30};
  }

  throw std::out_of_range("switch statement not matched");
}

Engine::Engine(const size_t size_input)
 : car(lanes[0]),
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

int Engine::GetRandomLane() const {
  int rand_loc = ci::randInt(0, lanes.size());
  if (occupied_lanes.empty()) {
    return rand_loc;
  }
  auto i = std::find(occupied_lanes.begin(), occupied_lanes.end(), lanes.at(rand_loc));
  while (i != occupied_lanes.end()) {
    rand_loc = ci::randInt(0, lanes.size());
    i = std::find(occupied_lanes.begin(), occupied_lanes.end(), lanes.at(rand_loc));
  }
  return rand_loc;
}

Car Engine::GetCar() const { return car; }

Coin Engine::GetCoin() const { return coin; }

Obstacle Engine::GetObstacle() const { return obstacle; }

void Engine::Step() {
  Location coin_loc = coin.GetLocation();
  Location obstacle_loc = obstacle.GetLocation();
  coin.SetLocation(Location(coin_loc.Row(), coin_loc.Col() + 50));
  obstacle.SetLocation(Location(obstacle_loc.Row(), obstacle_loc.Col() + 50));
  if (!(next_direction == Direction::left && car.GetLocation() == lanes[0]) &&
      !(next_direction == Direction::right &&
      car.GetLocation() == lanes[lanes.size() - 1])) {
    Location change_loc = FromDirection(next_direction);
    car.SetLocation(Location(car.GetLocation() + change_loc));
  }
}

void Engine::SetDirection(Direction direction) {
  next_direction = direction;
}

void Engine::Reset() {}
}  // namespace mylibrary
