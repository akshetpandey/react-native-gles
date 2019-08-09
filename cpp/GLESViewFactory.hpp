//
//  GLESViewFactory.hpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//

#include "GLESView.hpp"

#include <map>
#include <string>

#define REGISTER_SCENE(GLESView) \
__attribute__((constructor)) static void GLESView##_initalize() { \
    GLESViewFactory::registerView<GLESView>(#GLESView); \
}

template<typename T>
std::unique_ptr<GLESView> createT() { return std::make_unique<T>(); }

class GLESViewFactory {
public:
  template<class T>
  static void registerView(std::string const& s) {
    getViewMap()->insert(std::make_pair(s, &createT<T>));
  }
  
  typedef std::map<std::string, std::unique_ptr<GLESView>(*)()> ViewMap;
  
  static std::unique_ptr<GLESView> createView(std::string const& s);

  static ViewMap * getViewMap();
};
