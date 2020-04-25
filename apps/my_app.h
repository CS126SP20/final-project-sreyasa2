// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include "CinderImGui.h"
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"


namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  
 private:
  void DrawBackground();
  void DrawCar();
  void DrawCoin();  
  float car_rect_x1_factor = 1.35;
  float car_rect_y1_factor = 1.45;
  float car_rect_x2_factor = 0.79;
  float car_rect_y2_factor = 0.0;
  float coin_rect_x1_factor = 0.47;
  float coin_rect_y1_factor = 0.08;
  float coin_rect_x2_factor = 0.6;
  float coin_rect_y2_factor = 0.3;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
