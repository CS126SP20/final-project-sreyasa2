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
  
  void MoveCar();
  
  void Reset();
  
  void SetDirection(Direction);
  
  size_t GetScore() const;
  
  Car GetCar() const;
  
  std::vector<Obstacle> GetObstacle() const;
  
  std::vector<Coin> GetCoin() const;
  
  int GetRandomLane() const;
  
  const std::vector<Location> lanes{Location(170, 100), Location(290, 100),
                                    Location(410, 100),Location(530, 100)};
  
 private:
  Location GetObjectLocation();
  Location GetCarLocation();
  
 private:
  Car car;
  std::vector<Coin> coins;
  std::vector<Obstacle> obstacles;
  Direction next_direction;
  size_t size;
  std::vector<Location> occupied_lanes;
  int score;
};
}
#endif  // FINALPROJECT_ENGINE_H
