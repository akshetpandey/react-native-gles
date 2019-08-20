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


using SharedGLESView = std::shared_ptr<const GLESView>;

class GLESViewWrapper : public facebook::jsi::HostObject {
    friend class GLESManagerBinding;

    GLESViewWrapper(SharedGLESView glesView) : glesView(std::move(glesView)) {}
    
    SharedGLESView glesView;
};

class GLESManager {
public:
    
private:
    friend class GLESManagerBinding;
    
private:
    SharedGLESView createView(std::string sceneName);
};

class JSI_EXPORT GLESManagerBinding : public facebook::jsi::HostObject {
    
public:
    static void install(facebook::jsi::Runtime &runtime, std::shared_ptr<GLESManagerBinding> glesManagerBinding);
    
    GLESManagerBinding(std::unique_ptr<GLESManager> glesManager);
    
    facebook::jsi::Value get(facebook::jsi::Runtime& runtime, const facebook::jsi::PropNameID& propName);

private:
    std::unique_ptr<GLESManager> _glesManager;
};
