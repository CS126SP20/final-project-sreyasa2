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
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

namespace myapp {

using cinder::app::KeyEvent;
using ci::gl::Texture;
using namespace ci;
using namespace ci::app;

MyApp::MyApp():
    engine(size),
    game_state(GameState::Started){}
  

void MyApp::setup() {
  theme_mp3->start();
  ImGui::initialize(ui::Options().font(
      getAssetPath("Bebas-Regular.ttf"),
      60).window(getWindow()));
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  auto coin_image = loadImage( loadAsset( "coin.jpg"));
  texture2D_coin = ci::gl::Texture2d::create(coin_image);
  auto obstacle_image = loadImage(loadAsset("obstacle.jpg"));
  texture2D_obstacle = ci::gl::Texture2d::create(obstacle_image);
}

void MyApp::update() {
  if (game_state == GameState::Over) {
    theme_mp3->stop();
    if (!isEndMusicOn) {
      game_over_mp3->start();
      isEndMusicOn = true;
    }
    return;
  }

  if (game_state == GameState::Paused) {
    return;
  }
  
  if (engine.GetCar().GetHasCrashed()) {
    crash_mp3->start();
    game_state = GameState::Over;
    score = engine.GetScore();
  }
  
  if (engine.GetScore() == prev_score + 1) {
    coin_mp3->start();
    prev_score = engine.GetScore();
  }
  
  const auto time = std::chrono::system_clock::now();
  if (time - last_time_frame > std::chrono::milliseconds(speed)
  && game_state == GameState::Playing) {
    engine.Step();
    last_time_frame = time;
  }
}

void MyApp::draw() {
  ci::gl::clear(ci::Color(0, 0, 0));
  ci::gl::disableDepthRead();
  ci::gl::disableDepthWrite();
  ci::gl::enableAlphaBlending();
  
  if (game_state == GameState::Over) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));//delay for 1 second.
    DrawGameOver();
    return;
  }
  
  if (game_state == GameState::Paused) {
    DrawGamePause();
    return;
  }
  
  if (game_state == GameState::Started) {
    DrawGameStart();
  }
  
  if (game_state == GameState::Playing) {
    DrawBackground();
    DrawCoin();
    DrawObstacle();
    DrawCar();
  }
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
    if (coin_loc.Col() > engine.GetCar().GetLocation().Col()) { //to make up for delay between engine and draw
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
    if (obstacle_loc.Col() > engine.GetCar().GetLocation().Col()) { //to make up for delay between engine and draw
      continue;
    }
    ci::gl::draw(texture2D_obstacle,
                 ci::Rectf(obstacle_loc.Row(),
                           obstacle_loc.Col() - coin_height, 
                           obstacle_loc.Row() + lane_width, obstacle_loc.Col()));
  }
}

void MyApp::keyDown(KeyEvent event) { 
  switch (event.getCode()) {
    case KeyEvent::KEY_RIGHT: {
      if (game_state == GameState::Playing) {
        engine.SetDirection(mylibrary::Direction::right);
        engine.MoveCar();
      }
      break;
    }
    case KeyEvent::KEY_LEFT: {
      if (game_state == GameState::Playing) {
        engine.SetDirection(mylibrary::Direction::left);
        engine.MoveCar();
      }
      break;
    }
    case KeyEvent::KEY_p: {
      if (game_state == GameState::Playing) {
        game_state = GameState::Paused;
      }
      break;
    }
  }
}

void MyApp::DrawGameStart() {
  ci::gl::clear(ci::Color(0,0,0));
  ImGui::Begin("START");
  ImGui::Text("Instructions: \n use side-arrows to switch lanes. \n"
              "Collect coins. \n Hitting obstacles will cause crashes.");
  if (ImGui::Button("Start Game")) {
    game_state = GameState::Playing;
  }
  ImGui::End();
}

void MyApp::DrawGamePause() {
  ci::gl::clear(ci::Color(0,0,0));
  ImGui::Begin("PAUSE");
  if (ImGui::Button("Resume Game")) {
    game_state = GameState::Playing;
  }
  ImGui::End();
}

void MyApp::DrawGameOver() {
  ci::gl::clear(ci::Color(0,0,0));
  auto game_over = loadImage( loadAsset( "game_over.jpg"));
  ci::gl::Texture2dRef texture2D_gameOver = ci::gl::Texture2d::create(game_over);
  ci::gl::draw(texture2D_gameOver, getWindowBounds());
  std::string score_string = std::to_string(score);
  const char * scores = score_string.c_str();
  ImGui::Begin("Score");
  ImGui::Text("Your Score is: ");
  ImGui::Text("%s", scores);
  ImGui::End();
}

}  // namespace myapp
