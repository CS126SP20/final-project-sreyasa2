// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "CinderImGui.h"
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace myapp {

using cinder::app::KeyEvent;
using ci::gl::Texture;

MyApp::MyApp() { }

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() { }

void MyApp::draw() {
  ci::gl::clear(ci::Color( 0, 0, 0 ));
  ci::gl::disableDepthRead();
  ci::gl::disableDepthWrite();
  ci::gl::enableAlphaBlending();
  DrawBackground();
  DrawCar();
  DrawCoin();
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
  auto coin_image = loadImage( loadAsset( "coin.jpg"));
  ci::gl::Texture2dRef texture2D_coin = ci::gl::Texture2d::create(coin_image);
  ci::gl::draw(texture2D_coin,
               ci::Rectf(getWindowCenter().x * coin_rect_x1_factor,
                   getWindowCenter().y * coin_rect_y1_factor,
                   getWindowCenter().x * coin_rect_x2_factor,
                   getWindowCenter().y * coin_rect_y2_factor));
}

void MyApp::keyDown(KeyEvent event) { }


}  // namespace myapp
