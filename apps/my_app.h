// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <mylibrary/engine.h>
#include <mylibrary/location.h>
#include <mylibrary/obstacle.h>
#include <mylibrary/coin.h>
#include <mylibrary/car.h>
#include "CinderImGui.h"
#include "cinder/ImageIo.h"
#include "cinder/Vector.h"
#include "cinder/gl/Texture.h"

namespace myapp {

enum class GameState {
  Playing,
  Paused,
  Over,
};

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void enableFileLogging();
  void enableFileLoggingRotating();
  void enableSysLogging();
  
 private:
  void DrawBackground();
  void DrawCar();
  void DrawCoin();
  void DrawObstacle();
  void DrawTest();
  std::chrono::time_point<std::chrono::system_clock> last_time_frame;
  std::chrono::time_point<std::chrono::system_clock> last_time_car;
  GameState game_state;
  int lane_width = 95;
  int coin_height = 100;
  int car_height = 200;
  int speed_ = 300;
  int vert_dist = 50;
  int hori_dist = 30;
  const size_t size = 800;
  ci::gl::Texture2dRef texture2D_coin;
  ci::gl::Texture2dRef texture2D_obstacle;
  mylibrary::Engine engine;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
