//
// Created by sreya on 4/25/2020.
//

#ifndef FINALPROJECT_COIN_H
#define FINALPROJECT_COIN_H

#include "location.h"

namespace mylibrary {
class Coin {
 public:
  explicit Coin(const Location&);

  Coin(const Coin&);
  Coin(Coin&&) noexcept;
  Coin& operator=(const Coin&);
  Coin& operator=(Coin&&) noexcept;
  bool operator==(const Coin&);
  ~Coin();
  Location SetLocation(const Location&);
  Location GetLocation() const;

 private:
  Location location_;
  
};
}
#endif  // FINALPROJECT_COIN_H
