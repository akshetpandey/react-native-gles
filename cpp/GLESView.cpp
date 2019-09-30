//
//  GLESView.cpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//

#include "GLESView.hpp"

#include "GLESViewFactory.hpp"

REGISTER_SCENE(GLESView)

GLESView::GLESView(int64_t handle): handle_(handle) {
}

GLESView::~GLESView() {
}

int64_t GLESView::handle() const {
    return handle_;
}

facebook::jsi::Value GLESView::get(facebook::jsi::Runtime& runtime, const facebook::jsi::PropNameID& propName) {
    std::string methodName = propName.utf8(runtime);

    // When window.__GLESManagerBinding.createRenderer() is called, methodName == 'createRenderer'
    if (methodName == "handle") {
        return facebook::jsi::Function::createFromHostFunction(runtime,
                                                               propName,
                                                               1, // How many args does this method take
                                                               [=](facebook::jsi::Runtime &runtime,
                                                                              const facebook::jsi::Value &thisValue,
                                                                              const facebook::jsi::Value *arguments,
                                                                              size_t count) -> facebook::jsi::Value {
                                                                   return facebook::jsi::Value((int)this->handle());
                                                               });
    }

    return facebook::jsi::Value::undefined();
}
