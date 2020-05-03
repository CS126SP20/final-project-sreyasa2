// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "CinderImGui.h"
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"

#include <iostream>

namespace myapp {

using cinder::app::KeyEvent;
using ci::gl::Texture;
using namespace ci;
using namespace ci::app;

MyApp::MyApp():
    game_state{GameState::Playing},
    engine(size) {}
  

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  enableFileLogging();
  enableFileLoggingRotating();
  enableSysLogging();
}

void MyApp::update() {
  CI_LOG_V("Window bounds " << getWindowBounds());
  const auto time = std::chrono::system_clock::now();
  if (time - last_time_ > std::chrono::milliseconds(speed_)) {
    engine.Step();
    last_time_ = time;
  }
}

void MyApp::draw() {
  ci::gl::clear(ci::Color( 0, 0, 0 ));
  ci::gl::disableDepthRead();
  ci::gl::disableDepthWrite();
  ci::gl::enableAlphaBlending();
  DrawBackground();
  DrawCar();
  DrawCoin();
  DrawObstacle();
  //DrawTest();
}

void MyApp::DrawBackground() {
  auto background = loadImage( loadAsset( "background-1.jpg"));
  ci::gl::Texture2dRef texture2D_background = ci::gl::Texture2d::create(background);
  ci::gl::draw(texture2D_background, getWindowBounds());
}

void MyApp::DrawCar() {
  auto car_image = loadImage( loadAsset( "car.jpg"));
  ci::gl::Texture2dRef texture2D_car = ci::gl::Texture2d::create(car_image);
  mylibrary::Location car_loc = engine.GetCar().GetLocation();
  ci::gl::draw(texture2D_car,ci::Rectf(car_loc.Row(),
      getWindowHeight() - car_height, car_loc.Row() + lane_width,
          getWindowHeight()));
}

void MyApp::DrawCoin() {
  auto coin_image = loadImage( loadAsset( "coin.jpg"));
  ci::gl::Texture2dRef texture2D_coin = ci::gl::Texture2d::create(coin_image);
  mylibrary::Location coin_loc = engine.GetCoin().GetLocation();
  ci::gl::draw(texture2D_coin,ci::Rectf(coin_loc.Row(), coin_loc.Col(),
                   coin_loc.Row() + lane_width, coin_loc.Col() +
                   coin_height));
}

void MyApp::DrawObstacle() {
  auto obstacle_image = loadImage( loadAsset( "police_car.jpg"));
  ci::gl::Texture2dRef texture2D_coin = ci::gl::Texture2d::create(obstacle_image);
  mylibrary::Location obstacle_loc = engine.GetObstacle().GetLocation();
  ci::gl::draw(texture2D_coin,ci::Rectf(obstacle_loc.Row(), obstacle_loc.Col(),
                                        obstacle_loc.Row() +
                                        lane_width,obstacle_loc.Col() + car_height));
}

/*void MyApp::DrawTest() {
  ci::gl::drawSolidRect(ci::Rectf(290, 150, 385, 250));
  ci::gl::drawSolidRect(ci::Rectf(170, 150, 265, 250));
  ci::gl::drawSolidRect(ci::Rectf(410, 150, 505, 250));
  ci::gl::drawSolidRect(ci::Rectf(530, 150, 625, 250));
}*/

void MyApp::keyDown(KeyEvent event) { 
  switch (event.getCode()) {
    case KeyEvent::KEY_RIGHT: {
      engine.SetDirection(mylibrary::Direction::right);
      break;
    }
    case KeyEvent::KEY_LEFT: {
      engine.SetDirection(mylibrary::Direction::left);
      break;
    }
  }
}

void MyApp::enableFileLogging()
{
 log::makeLogger<log::LoggerFile>( "/tmp/logging/cinder.log", true );
}

void MyApp::enableFileLoggingRotating()
{
  log::makeLogger<log::LoggerFileRotating>( "/tmp/logging", "cinder.%Y.%m.%d.log" );
}

void MyApp::enableSysLogging()
{
  auto sysLogger = log::makeLogger<log::LoggerSystem>();
  sysLogger->setLoggingLevel( log::LEVEL_WARNING );
}


}  // namespace myapp
