//
//  GLESManager.cpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//

#include "GLESManager.hpp"
#include "GLESViewFactory.hpp"

static facebook::jsi::Object getModule(facebook::jsi::Runtime &runtime, const std::string &moduleName) {
    auto batchedBridge =
    runtime.global().getPropertyAsObject(runtime, "__fbBatchedBridge");
    auto getCallableModule =
    batchedBridge.getPropertyAsFunction(runtime, "getCallableModule");
    auto module = getCallableModule.callWithThis(runtime,
                                                 batchedBridge,
                                                 {facebook::jsi::String::createFromUtf8(runtime, moduleName)}
                                                 ).asObject(runtime);
    return module;
}

inline static facebook::jsi::Value valueFromGLESView(facebook::jsi::Runtime &runtime, const GLESViewWrapper &glesView) {
    return facebook::jsi::Object::createFromHostObject(runtime, std::make_shared<GLESViewWrapper>(glesView));
}

void GLESManagerBinding::install(facebook::jsi::Runtime &runtime, std::shared_ptr<GLESManagerBinding> glesManagerBinding) {
    auto moduleName = "__GLESManagerBinding";
    auto object = facebook::jsi::Object::createFromHostObject(runtime, glesManagerBinding);
    runtime.global().setProperty(runtime, moduleName, std::move(object));
}

GLESManagerBinding::GLESManagerBinding(std::unique_ptr<GLESManager> glesManager) : _glesManager(std::move(glesManager)) {
    
}

facebook::jsi::Value GLESManagerBinding::get(facebook::jsi::Runtime& runtime, const facebook::jsi::PropNameID& name) {
    std::string methodName = name.utf8(runtime);
    auto glesManager = *_glesManager;

    // When window.__GLESManagerBinding.createRenderer() is called, methodName == 'createRenderer'
    if (methodName == "createRenderer") {
        return facebook::jsi::Function::createFromHostFunction(runtime,
                                                               name,
                                                               1, // How many args does this method take
                                                               [&glesManager](facebook::jsi::Runtime &runtime,
                                                                              const facebook::jsi::Value &thisValue,
                                                                              const facebook::jsi::Value *arguments,
                                                                              size_t count) -> facebook::jsi::Value {
                                                                   auto rendererName = arguments[0].asString(runtime).utf8(runtime);
                                                                   auto renderer = GLESViewFactory::createView(rendererName);
                                                                   if (renderer) {
                                                                       auto rendererWrapper = GLESViewWrapper(std::shared_ptr<const GLESView>(std::move(renderer)));
                                                                       return valueFromGLESView(runtime, rendererWrapper);
                                                                   }
                                                                   return facebook::jsi::Value::undefined();
                                                               });
    }

    return facebook::jsi::Value::undefined();
}
