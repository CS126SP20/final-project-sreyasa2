// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "CinderImGui.h"
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"
#include <mylibrary/location.h>
#include <mylibrary/obstacle.h>
#include <mylibrary/coin.h>
#include "vector"
#include <chrono>
#include <mylibrary/car.h>
#include <iostream>

namespace myapp {

using cinder::app::KeyEvent;
using ci::gl::Texture;
using namespace ci;
using namespace ci::app;

const char BoldFont[] = "Arial Bold";

MyApp::MyApp():
    game_state{GameState::Playing},
    engine(size) {}
  

void MyApp::setup() {
  ImGui::initialize(ui::Options().font(
      getAssetPath("Bebas-Regular.ttf"),
      12).window(getWindow()));
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  enableFileLogging();
  enableFileLoggingRotating();
  enableSysLogging();
  auto coin_image = loadImage( loadAsset( "coin.jpg"));
  texture2D_coin = ci::gl::Texture2d::create(coin_image);
  auto obstacle_image = loadImage(loadAsset("obstacle.jpg"));
  texture2D_obstacle = ci::gl::Texture2d::create(obstacle_image);
}

void MyApp::update() {
  if (engine.GetCar().GetHasCrashed()) {
    game_state = GameState::Over;
    score = engine.GetScore();
  }
  CI_LOG_V("Window bounds " << getWindowBounds());
  const auto time = std::chrono::system_clock::now();
  if (time - last_time_frame > std::chrono::milliseconds(300)
  && game_state == GameState::Playing) {
    engine.Step();
    last_time_frame = time;
  }
}

void MyApp::draw() {
  ci::gl::clear(ci::Color( 0, 0, 0 ));
  ci::gl::disableDepthRead();
  ci::gl::disableDepthWrite();
  ci::gl::enableAlphaBlending();
  DrawBackground();
  DrawCoin();
  DrawObstacle();
  DrawCar();
  const auto time = std::chrono::system_clock::now();
  if ((game_state == GameState::Over)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    DrawGameOver();
    return;
  }
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
  std::vector<mylibrary::Coin> coins = engine.GetCoin();
  for (int i = 0; i < coins.size(); i++) {
    mylibrary::Location coin_loc = coins[i].GetLocation();
    if (coin_loc.Col() > 550) {
      continue;
    }
    ci::gl::draw(texture2D_coin, ci::Rectf(coin_loc.Row(),
                                           coin_loc.Col() - coin_height,
                                           coin_loc.Row() + lane_width, coin_loc.Col()));
  }
}

void MyApp::DrawObstacle() {
  std::vector<mylibrary::Obstacle> obstacles = engine.GetObstacle();
  for (int i = 0; i < obstacles.size(); i++) {
    mylibrary::Location obstacle_loc = obstacles[i].GetLocation();
    if (obstacle_loc.Col() > 550) {
      continue;
    }
    ci::gl::draw(texture2D_obstacle,
                 ci::Rectf(obstacle_loc.Row(),
                           obstacle_loc.Col() - coin_height, 
                           obstacle_loc.Row() + lane_width, obstacle_loc.Col()));
  }
}

void MyApp::DrawGameOver() {
  ci::gl::clear(ci::Color(0,0,0));
  std::string score_string = std::to_string(score);
  ImGui::Text("Game Over :( \n Score is:");
}

void MyApp::keyDown(KeyEvent event) { 
  switch (event.getCode()) {
    case KeyEvent::KEY_RIGHT: {
      engine.SetDirection(mylibrary::Direction::right);
      engine.MoveCar();
      break;
    }
    case KeyEvent::KEY_LEFT: {
      engine.SetDirection(mylibrary::Direction::left);
      engine.MoveCar();
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
