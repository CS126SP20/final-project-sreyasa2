//
// Created by sreya on 4/25/2020.
//

#ifndef FINALPROJECT_OBSTACLE_H
#define FINALPROJECT_OBSTACLE_H

#include "location.h"

namespace mylibrary {
class Obstacle {
 public:
  explicit Obstacle(const Location&);
  Location GetLocation() const;
  Location SetLocation(const Location&);
  Obstacle(const Obstacle&);
  Obstacle(Obstacle&&) noexcept;
  Obstacle& operator=(const Obstacle&);
  Obstacle& operator=(Obstacle&&) noexcept;
  bool operator==(const Obstacle&);
  ~Obstacle();
  
 private:
  Location location;
};
}
#endif  // FINALPROJECT_OBSTACLE_H
