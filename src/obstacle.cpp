//
// Created by sreya on 4/25/2020.
//

#include "mylibrary/obstacle.h"

namespace mylibrary {

Obstacle::Obstacle(const Location& location) : location(location) {}

Location Obstacle::GetLocation() const { return location; }

Obstacle::Obstacle(const Obstacle& Obstacle) = default;

Obstacle::Obstacle(mylibrary::Obstacle&& Obstacle) noexcept = default;

Obstacle& Obstacle::operator=(const Obstacle& Obstacle) = default;

Obstacle& Obstacle::operator=(mylibrary::Obstacle&& Obstacle) noexcept = default;

Obstacle::~Obstacle() = default;

Location Obstacle::SetLocation(const Location& location_set) {
  location = location_set;
  return location;
}

} // namespace mylibrary