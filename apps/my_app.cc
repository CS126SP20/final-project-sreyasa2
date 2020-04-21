// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include "CinderImGui.h"
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>;

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::initialize();
}

void MyApp::update() { }

void MyApp::draw() {
  ci::gl::clear(ci::Color( 0, 0, 0 ) );
  ImGui::Text("Hello, world!");
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
