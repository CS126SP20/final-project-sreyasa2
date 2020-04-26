//
// Created by sreya on 4/23/2020.
//

#ifndef FINALPROJECT_CAR_H
#define FINALPROJECT_CAR_H

#include "location.h"

namespace mylibrary {

class Car {
 public:
  explicit Car(const Location& location);
  Location GetLocation() const;
  Location SetLocation(const Location&);
  
 private:
  Location location;
  bool hasCrashed;
};
}
#endif  // FINALPROJECT_CAR_H
