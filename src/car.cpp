//
// Created by sreya on 4/23/2020.
//

#include "mylibrary/car.h"

namespace mylibrary {

Car::Car(const Location& location_set) :
  location(location_set), hasCrashed{false} {}

Location Car::GetLocation() const { return location; }

Location Car::SetLocation(const Location& location_set) {
  location = location_set;
  return location;
}

}