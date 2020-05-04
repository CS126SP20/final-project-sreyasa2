//
// Created by sreya on 4/25/2020.
//

#include "mylibrary/coin.h"

namespace mylibrary {

Coin::Coin(const Location& location) : location_(location) {}

Location Coin::GetLocation() const { return location_; }
Location Coin::SetLocation(const Location& location) {
  location_ = location;
  return location_;
}
bool Coin::operator==(const Coin& rhs) { return location_ == rhs.GetLocation(); }

Coin::Coin(const Coin& Coin) = default;
Coin::Coin(mylibrary::Coin&& Coin) noexcept = default;
Coin& Coin::operator=(const Coin& Coin) = default;
Coin& Coin::operator=(mylibrary::Coin&& Coin) noexcept = default;
Coin::~Coin() = default;

}  //namespace mylibrary