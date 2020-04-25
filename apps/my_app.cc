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
  auto background = loadImage( loadAsset( "background-1.jpg"));
  texture2D_background = ci::gl::Texture2d::create(background);
  auto car_image = loadImage( loadAsset( "car.jpg"));
  texture2D_car = ci::gl::Texture2d::create(car_image);
}

void MyApp::update() { }

void MyApp::draw() {
  ci::gl::clear(ci::Color( 0, 0, 0 ));
  ci::gl::disableDepthRead();
  ci::gl::disableDepthWrite();
  ci::gl::enableAlphaBlending();
  DrawBackground();
  DrawCar();
}

void MyApp::DrawBackground() {
  ci::gl::draw(texture2D_background, getWindowBounds());
}

void MyApp::DrawCar() {
  ci::gl::draw(texture2D_car, getWindowCenter());
}

void MyApp::keyDown(KeyEvent event) { }


}  // namespace myapp
