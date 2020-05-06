// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <mylibrary/engine.h>
#include <mylibrary/location.h>
#include <mylibrary/example.h>

using namespace mylibrary;

TEST_CASE("Random Location in lane", "[Location][engine]") {
  mylibrary::Engine engine(800);
  const std::vector<mylibrary::Location> lanes{mylibrary::Location(170, 100), mylibrary::Location(290, 100),
                                    mylibrary::Location(410, 100),mylibrary::Location(530, 100)};
  mylibrary::Location test_location(engine.GetObjectLocation());
  auto i = std::find(lanes.begin(), lanes.end(), test_location);
  REQUIRE(i != lanes.end());
}

TEST_CASE("Initial Score", "[Constructor]") {
  mylibrary::Engine engine(800);
  REQUIRE(engine.GetScore() == 0);
}

TEST_CASE("Initial Car", "[Constructor]") {
  mylibrary::Engine engine(800);
  REQUIRE(engine.GetCar().GetLocation() == mylibrary::Location(170, 550));
}

TEST_CASE("Initial Obstacles", "[Constructor]") {
  mylibrary::Engine engine(800);
  REQUIRE(engine.GetObstacle().size() == 1);
}

TEST_CASE("Initial Coins", "[Constructor]") {
  mylibrary::Engine engine(800);
  REQUIRE(engine.GetCoin().size() == 1);
}

TEST_CASE("Step adds coins", "[Engine]") {
  mylibrary::Engine engine(800);
  engine.Step();
  REQUIRE(engine.GetCoin().size() == 2);
}

TEST_CASE("Step moves coins", "[Engine]") {
  Engine engine(800);
  Location before_step = engine.GetCoin()[0].GetLocation();
  engine.Step();
  Location after_step = engine.GetCoin()[0].GetLocation();
  REQUIRE(after_step.Col() - before_step.Col() == 150);
}

TEST_CASE("Step moves obstacles", "[Engine]") {
  Engine engine(800);
  Location before_step = engine.GetObstacle()[0].GetLocation();
  engine.Step();
  Location after_step = engine.GetObstacle()[0].GetLocation();
  REQUIRE(after_step.Col() - before_step.Col() == 150);
}

TEST_CASE("Car moves when possible", "[Engine]") {
  Engine engine(800);
  int row_before_moving = engine.GetCar().GetLocation().Row();
  engine.SetDirection(Direction::right);
  engine.MoveCar();
  REQUIRE(engine.GetCar().GetLocation().Row() - row_before_moving == 120);
}

TEST_CASE("Car does not move when on edge", "[Engine]") {
  Engine engine(800);
  int row_before_moving = engine.GetCar().GetLocation().Row();
  engine.SetDirection(Direction::left);
  engine.MoveCar();
  REQUIRE(engine.GetCar().GetLocation().Row() - row_before_moving == 0);
}