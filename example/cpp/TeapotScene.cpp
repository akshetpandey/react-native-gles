//
//  TeapotScene.cpp
//  RNOpenGL
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019 Facebook. All rights reserved.
//
#include "TeapotScene.hpp"
#include "GLESViewFactory.hpp"

REGISTER_SCENE(TeapotScene)

TeapotScene::TeapotScene(int64_t handle) noexcept
: GLESView(handle),
fx_(0),
fy_(1),
delta_(0.01)  {
  ndk_helper::Vec2 vec(fx_, fy_);
  renderer_.Bind(&tap_camera_);
  tap_camera_.SetFlip(1, 1, 1);
  tap_camera_.SetPinchTransformFactor(2.f, 2.f, 8.f);
  tap_camera_.BeginDrag(vec);
}

void TeapotScene::initializeGL() {
  renderer_.Init();
}

void TeapotScene::destroyGL() {
  renderer_.Unload();
}

bool TeapotScene::update(double timestamp) {
  ndk_helper::Vec2 vec(fx_, fy_);
  tap_camera_.Drag(vec);
  renderer_.Update(timestamp);
  
  fx_ += delta_;
  if (fx_ >= 1.0f) {
    delta_ = -0.01f;
  } else if (fx_ <= -1.0f) {
    delta_ = 0.01f;
  }
  
  return true;
}

void TeapotScene::draw() {
  glClearColor(0.f, 0.f, 0.f, 0.25f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  renderer_.UpdateViewport();
  renderer_.Render();
}
