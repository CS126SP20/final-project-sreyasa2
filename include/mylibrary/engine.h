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

namespace mylibrary {

enum class Direction {left, right};

class Engine {
  
 public:
  
  Engine();
  
  Engine(unsigned seed);
  
  void Step();
  
  void Reset();
  
  void SetDirection(Direction);
  
  size_t GetScore() const;
  
  Car GetCar() const;
  
  Obstacle GetObstacle() const;
  
  Coin GetCoin() const;
  
 private:
  Location GetLocationOnBoard();
  std::set<Location> GetOccupiedTiles();
  
 private:
  Car car;
  Coin coin;
  Obstacle obstacle;
  Direction next_direction;  
};
}
#endif  // FINALPROJECT_ENGINE_H
