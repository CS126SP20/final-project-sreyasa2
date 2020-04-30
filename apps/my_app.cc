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
    game_state{GameState::Playing} {}
  

void MyApp::setup() {
  std::cout << "Hello" << std::endl;
  CI_LOG_D("ello");
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  enableFileLogging();
  enableFileLoggingRotating();
  enableSysLogging();
}

void MyApp::update() {
  CI_LOG_V("Window bounds " << getWindowBounds());
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
}

void MyApp::DrawBackground() {
  auto background = loadImage( loadAsset( "background-1.jpg"));
  ci::gl::Texture2dRef texture2D_background = ci::gl::Texture2d::create(background);
  ci::gl::draw(texture2D_background, getWindowBounds());
}

void MyApp::DrawCar() {
  auto car_image = loadImage( loadAsset( "car.jpg"));
  ci::gl::Texture2dRef texture2D_car = ci::gl::Texture2d::create(car_image);
  ci::gl::draw(texture2D_car,
      ci::Rectf(getWindowCenter().x*car_rect_x1_factor,
          getWindowCenter().y*car_rect_y1_factor, getWindowWidth()*car_rect_x2_factor,
          getWindowHeight() + car_rect_y2_factor));
}

void MyApp::DrawCoin() {
  //TODO: make the coin wider
  auto coin_image = loadImage( loadAsset( "coin.jpg"));
  ci::gl::Texture2dRef texture2D_coin = ci::gl::Texture2d::create(coin_image);
  ci::gl::draw(texture2D_coin,
               ci::Rectf(getWindowCenter().x * coin_rect_x1_factor,
                   getWindowCenter().y * coin_rect_y1_factor,
                   getWindowCenter().x * coin_rect_x2_factor,
                   getWindowCenter().y * coin_rect_y2_factor));
}

void MyApp::DrawObstacle() {}

void MyApp::keyDown(KeyEvent event) { }

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
