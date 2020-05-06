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
#include "cinder/audio/audio.h"

namespace myapp {

using namespace ci;

enum class GameState {
  Playing,
  Started,
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
  
 private:
  
  void DrawBackground();
  void DrawCar();
  void DrawCoin();
  void DrawObstacle();
  void DrawGameOver();
  void DrawGameStart();
  void DrawGamePause();
  std::chrono::time_point<std::chrono::system_clock> last_time_frame;
  GameState game_state;
  int lane_width = 95;
  int coin_height = 100;
  int car_height = 200;
  const size_t size = 800;
  int score = 0;
  int coin_number = 0;
  int speed = 300;
  /*ci::audio::SourceFileRef theme_song = audio::load(
      app::loadAsset("theme_song.mp3"));
  audio::VoiceRef theme_mp3 = audio::Voice::create(theme_song);
  ci::audio::SourceFileRef game_over_song = audio::load(
      app::loadAsset("game_over_sound.mp3"));
  audio::VoiceRef game_over_mp3 = audio::Voice::create(game_over_song);
  ci::audio::SourceFileRef coin_sound = audio::load(
      app::loadAsset("coin_sound.mp3"));
  audio::VoiceRef coin_mp3 = audio::Voice::create(coin_sound);
  ci::audio::SourceFileRef crash_sound = audio::load(
      app::loadAsset("car_crash.mp3"));
  audio::VoiceRef crash_mp3 = audio::Voice::create(theme_song);*/
  ci::gl::Texture2dRef texture2D_coin;
  ci::gl::Texture2dRef texture2D_obstacle;
  mylibrary::Engine engine;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
