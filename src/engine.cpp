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
      return {-125, 0};
    case Direction::right:
      return {125, 0};
  }

  throw std::out_of_range("switch statement not matched");
}

Engine::Engine(const size_t size_input)
 : car(lanes[0]),
   next_direction(Direction::left) {
  obstacles.emplace_back(lanes[1]);
  coins.emplace_back(lanes[0]);
  occupied_lanes.push_back(obstacles[0].GetLocation());
  occupied_lanes.push_back(coins[0].GetLocation());
     size = size_input;
     occupied_lanes = {};
     score = 0;
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

std::vector<Coin> Engine::GetCoin() const { return coins; }

std::vector<Obstacle> Engine::GetObstacle() const { return obstacles; }

void Engine::Step() {
  for (int i = 0; i < coins.size(); i++) {
    Location coin_loc = coins[i].GetLocation();
    coins[i].SetLocation(Location(coin_loc.Row(), coin_loc.Col() + 50));
    if (coins[i].GetLocation().Col() >= size) {
      auto iterator = std::find(coins.begin(), coins.end(), coins[i]);
      coins.erase(iterator);
    }
  }
  for (int i = 0; i < obstacles.size(); i++) {
    Location obstacle_loc = obstacles[i].GetLocation();
    obstacles[i].SetLocation(Location(obstacle_loc.Row(), obstacle_loc.Col() + 50));
    if (obstacles[i].GetLocation().Col() >= size) {
      auto iterator = std::find(obstacles.begin(), obstacles.end(), obstacles[i]);
      obstacles.erase(iterator);
    }
  }
  occupied_lanes.clear();
  for (int i = 0; i < 2; i++) {
    Coin new_coin(GetObjectLocation());
    coins.push_back(new_coin);
  }
  for (int i = 0; i < 2; i++) {
    Obstacle new_obstacle(GetObjectLocation());
    obstacles.push_back(new_obstacle);
  }
}

void Engine::MoveCar() {
  if (!(next_direction == Direction::left && car.GetLocation() == lanes[0]) &&
      !(next_direction == Direction::right &&
        car.GetLocation() == lanes[lanes.size() - 1])) {
    Location change_loc = FromDirection(next_direction);
    car.SetLocation(Location(car.GetLocation() + change_loc));
  } 
  for (int i = 0; i < coins.size(); i++) {
    if (car.GetLocation() == coins[i].GetLocation()) {
      score++;
      auto iterator = std::find(coins.begin(), coins.end(), coins[i]);
      coins.erase(iterator);
      break;
    }
  }
  for (int i = 0; i < obstacles.size(); i++) {
    if (car.GetLocation() == obstacles[i].GetLocation()) {
      car.Crash();
      break;
    }
  }
}
void Engine::SetDirection(Direction direction) {
  next_direction = direction;
}

void Engine::Reset() {}
}  // namespace mylibrary
