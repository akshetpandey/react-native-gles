//
//  GLESView.hpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//
#pragma once

#include <cstdint>

#include <jsi/jsi.h>

class GLESViewFactory;

class JSI_EXPORT GLESView : public facebook::jsi::HostObject {
    friend class GLESViewFactory;

public:
    GLESView(int64_t handle);

    int64_t handle() const;
    
    // [any thread]
    // GL context is not set
    virtual ~GLESView();

    // [gl loader thread]
    // GL context is set for current thread
    // Renderbuffer, Framebuffers, view ports and other window related values may not be set yet
    virtual void initializeGL() { };

    // [gl loader thread]
    // GL context is set for current thread
    virtual void destroyGL() { };

    // [rendering thread]
    // GL context is not set
    // Do not issue any draw calls
    // Only called after initializeGL returns
    virtual bool update(double timestamp) { return false; };

    // [rendering thread]
    // GL context is set for current thread
    // Only issue draw calls, do not update any state
    virtual void draw() { }

    virtual facebook::jsi::Value get(facebook::jsi::Runtime& runtime, const facebook::jsi::PropNameID& propName);
private:
    int64_t handle_;
};
