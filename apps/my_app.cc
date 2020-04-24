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
  mTex = ci::gl::Texture2d::create(background);
}

void MyApp::update() { }

void MyApp::draw() {
  ci::gl::clear(ci::Color( 0, 0, 0 ) );
  ci::gl::draw( mTex, getWindowBounds());
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
