//
//  GLESView.hpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//
#pragma once

#include <map>
#include <string>

class GLESView {
public:
  virtual ~GLESView() = default;

  virtual bool update(double timestamp) { return false; };

  virtual void draw() { }
};
