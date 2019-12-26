//
//  GLESManager.hpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//
#pragma once

#include <memory>
#include <string>

#include <jsi/jsi.h>

#include "GLESView.hpp"

class JSI_EXPORT GLESManagerBinding : public facebook::jsi::HostObject {
public:
    static void install(facebook::jsi::Runtime &runtime, std::shared_ptr<GLESManagerBinding> glesManagerBinding);

    GLESManagerBinding();

    facebook::jsi::Value get(facebook::jsi::Runtime& runtime, const facebook::jsi::PropNameID& propName);
};
