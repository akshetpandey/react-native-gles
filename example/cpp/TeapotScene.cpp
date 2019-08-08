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

TeapotScene::TeapotScene() noexcept : didInit_(false), fx_(0), fy_(0.5), delta_(0.01)  {
}

bool TeapotScene::update(double timestamp) {
  if (!didInit_) {
    return true;
  }
  ndk_helper::Vec2 vec(fx_, fy_);
  tap_camera_.Drag(vec);
  renderer_.Update(timestamp);

  fx_ += delta_;
  if (fx_ >= 1.0) {
    delta_ = -0.01;
  } else if (fx_ <= 0) {
    delta_ = 0.01;
  }

  return true;
}

void TeapotScene::draw() {
  if (!didInit_) {
    ndk_helper::Vec2 vec(fx_, fy_);
    renderer_.Init();
    renderer_.Bind(&tap_camera_);
    renderer_.UpdateViewport();
    tap_camera_.SetFlip(1.f, -1.f, -1.f);
    tap_camera_.SetPinchTransformFactor(2.f, 2.f, 8.f);
    didInit_ = true;
    tap_camera_.BeginDrag(vec);
  }

  glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  renderer_.Render();
}
