//
//  TeapotScene.hpp
//  RNOpenGL
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019 Facebook. All rights reserved.
//
#pragma once

#include "GLESView.hpp"

#include "TeapotRenderer/TeapotRenderer.h"
#include "NDKHelper/NDKHelper.h"

class TeapotScene : public GLESView {
  public:
    TeapotScene(int64_t handle) noexcept;
    void initializeGL();
    void destroyGL();
    bool update(double timestamp);
    void draw();
  private:
    float fx_;
    float fy_;
    float delta_;
    TeapotRenderer renderer_;
    ndk_helper::TapCamera tap_camera_;
};
