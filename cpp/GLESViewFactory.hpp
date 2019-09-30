//
//  GLESViewFactory.hpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//
#pragma once

#include <cstdint>
#include <string>

#include "GLESView.hpp"

#define REGISTER_SCENE(GLESView) \
__attribute__((constructor)) static void GLESView##_initalize() { \
    GLESViewFactory::registerView<GLESView>(#GLESView); \
}

template<typename T>
std::shared_ptr<GLESView> createT(int64_t handle) { return std::make_shared<T>(handle); }

class GLESViewFactory {
public:
  template<class T>
  static void registerView(std::string const& s) {
    GLESViewFactory::registerViewConstructor(s, &createT<T>);
  }
  
  static std::shared_ptr<GLESView> createView(std::string const& s);
  static void destroyView(std::shared_ptr<GLESView> view);
  static std::shared_ptr<GLESView> getView(int64_t handle);

private:
  static void registerViewConstructor(std::string const& s, std::shared_ptr<GLESView>(constructor)(int64_t));
};
