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
    TeapotScene() noexcept;
    bool update(double timestamp);
    void draw();
  private:
    bool didInit_;
    float fx_;
    float fy_;
    float delta_;
    TeapotRenderer renderer_;
    ndk_helper::TapCamera tap_camera_;
};
