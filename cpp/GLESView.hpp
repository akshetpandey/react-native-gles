//
//  GLESView.h
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//
#pragma once

#include <map>
#include <string>

#if __has_include(<OpenGLES/ES2/gl.h>)
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif __has_include(<GLES2/gl2.h>)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#define REGISTER_SCENE(GLESView) \
__attribute__((constructor)) static void GLESView##_initalize() { \
    GLESViewFactory::registerView<GLESView>(#GLESView); \
}

class GLESView {
public:
  virtual ~GLESView() = default;

  virtual bool update(double timestamp) { return false; };

  virtual void draw() {
    glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
};

template<typename T>
std::unique_ptr<GLESView> createT() { return std::make_unique<T>(); }

class GLESViewFactory {
public:
  typedef std::map<std::string, std::unique_ptr<GLESView>(*)()> ViewMap;

  template<class T>
  static void registerView(std::string const& s) {
    getViewMap()->insert(std::make_pair(s, &createT<T>));
  }
  
  static std::unique_ptr<GLESView> createView(std::string const& s) {
    auto it = getViewMap()->find(s);
    if (it == getViewMap()->end()) {
      return nullptr;
    }
    return it->second();
  }

  static ViewMap * getViewMap() {
    static ViewMap *viewMap = new ViewMap;
    return viewMap;
  }
};

REGISTER_SCENE(GLESView)

