//
//  GLESManager.cpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//

#include "GLESManager.hpp"
#include "GLESViewFactory.hpp"

inline static facebook::jsi::Value valueFromGLESView(facebook::jsi::Runtime &runtime, std::shared_ptr<GLESView> glesView) {
    return facebook::jsi::Object::createFromHostObject(runtime, glesView);
}

void GLESManagerBinding::install(facebook::jsi::Runtime &runtime, std::shared_ptr<GLESManagerBinding> glesManagerBinding) {
    auto moduleName = "__GLESManagerBinding";
    auto object = facebook::jsi::Object::createFromHostObject(runtime, glesManagerBinding);
    runtime.global().setProperty(runtime, moduleName, std::move(object));
}

GLESManagerBinding::GLESManagerBinding() {
    
}

facebook::jsi::Value GLESManagerBinding::get(facebook::jsi::Runtime& runtime, const facebook::jsi::PropNameID& name) {
    std::string methodName = name.utf8(runtime);

    // When window.__GLESManagerBinding.createRenderer() is called, methodName == 'createRenderer'
    if (methodName == "createRenderer") {
        return facebook::jsi::Function::createFromHostFunction(runtime,
                                                               name,
                                                               1, // How many args does this method take
                                                               [](facebook::jsi::Runtime &runtime,
                                                                              const facebook::jsi::Value &thisValue,
                                                                              const facebook::jsi::Value *arguments,
                                                                              size_t count) -> facebook::jsi::Value {
                                                                   auto rendererName = arguments[0].asString(runtime).utf8(runtime);
                                                                   auto renderer = GLESViewFactory::createView(rendererName);
                                                                   if (renderer) {
                                                                       return valueFromGLESView(runtime, renderer);
                                                                   }
                                                                   return facebook::jsi::Value::undefined();
                                                               });
    }
    if (methodName == "destroyRenderer") {
        return facebook::jsi::Function::createFromHostFunction(runtime,
                                                               name,
                                                               1, // How many args does this method take
                                                               [](facebook::jsi::Runtime &runtime,
                                                                              const facebook::jsi::Value &thisValue,
                                                                              const facebook::jsi::Value *arguments,
                                                                              size_t count) -> facebook::jsi::Value {
                                                                   auto view = arguments[0].asObject(runtime).getHostObject<GLESView>(runtime);
                                                                   GLESViewFactory::destroyView(view);
                                                                   return facebook::jsi::Value::undefined();
                                                               });
    }

    return facebook::jsi::Value::undefined();
}
