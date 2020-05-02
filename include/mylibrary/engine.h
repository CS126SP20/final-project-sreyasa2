//
// Created by sreya on 4/23/2020.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "obstacle.h"
#include "car.h"
#include "coin.h"
#include <set>
#include <random>
#include <list>
#include "cinder/Rand.h"

namespace mylibrary {

enum class Direction {left, right};

class Engine {
  
 public:
  
  explicit Engine(const size_t size);
    
  void Step();
  
  void Reset();
  
  void SetDirection(Direction);
  
  size_t GetScore() const;
  
  Car GetCar() const;
  
  Obstacle GetObstacle() const;
  
  Coin GetCoin() const;
  
  int GetRandomLane() const;
  
  const std::vector<Location> lanes{Location(170, 0), Location(290, 0),
                                    Location(410, 0),Location(530, 0)};
  
 private:
  Location GetObjectLocation();
  Location GetCarLocation();
  
 private:
  Car car;
  Coin coin;
  Obstacle obstacle;
  Direction next_direction;
  size_t size;
  std::vector<Location> occupied_lanes;
};
}
#endif  // FINALPROJECT_ENGINE_H
