//
//  GLESViewFactory.cpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//

#include "GLESViewFactory.hpp"

GLESViewFactory::ViewMap * GLESViewFactory::getViewMap() {
    static auto *viewMap = new ViewMap;
    return viewMap;
}

std::unique_ptr<GLESView> GLESViewFactory::createView(std::string const& s) {
    auto it = getViewMap()->find(s);
    if (it == getViewMap()->end()) {
        return nullptr;
    }
    return it->second();
}
