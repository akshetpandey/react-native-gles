//
//  GLESViewFactory.cpp
//  RNGLESView
//
//  Created by Akshet Pandey on 7/30/19.
//  Copyright © 2019. All rights reserved.
//

#include "GLESViewFactory.hpp"

#include <mutex>
#include <map>

typedef std::map<int64_t, std::shared_ptr<GLESView>> HandleMap;
typedef std::map<std::string, std::shared_ptr<GLESView>(*)(int64_t)> ViewNameMap;

static ViewNameMap * getViewNameMap();

static int64_t currentHandle = 0;
static std::mutex createHandleMutex;
static std::mutex handleMapMutex;

int64_t createHandle() {
    std::lock_guard<std::mutex> lock(createHandleMutex);
    int64_t handle = currentHandle;
    currentHandle += 1;
    return handle;
}

HandleMap *getHandleMap() {
    static auto handleMap = new HandleMap;
    return handleMap;
}

ViewNameMap * getViewNameMap() {
    static auto *viewMap = new ViewNameMap;
    return viewMap;
}

void saveView(std::shared_ptr<GLESView> view) {
    std::lock_guard<std::mutex> lock(handleMapMutex);
    auto handleMap = getHandleMap();
    handleMap->insert(std::make_pair(view->handle(), view));
}

void removeView(std::shared_ptr<GLESView> view) {
    std::lock_guard<std::mutex> lock(handleMapMutex);
    auto handleMap = getHandleMap();
    handleMap->erase(view->handle());
}

void GLESViewFactory::registerViewConstructor(std::string const& s, std::shared_ptr<GLESView>(constructor)(int64_t)) {
    getViewNameMap()->insert(std::make_pair(s, constructor));
}

std::shared_ptr<GLESView> GLESViewFactory::createView(std::string const& s) {
    auto it = getViewNameMap()->find(s);
    if (it == getViewNameMap()->end()) {
        return nullptr;
    }
    auto handle = createHandle();
    auto view = it->second(handle);
    saveView(view);
    return view;
}

void GLESViewFactory::destroyView(std::shared_ptr<GLESView> view) {
    removeView(view);
}

std::shared_ptr<GLESView> GLESViewFactory::getView(int64_t handle) {
    std::lock_guard<std::mutex> lock(handleMapMutex);
    auto handleMap = getHandleMap();
    auto viewIt = handleMap->find(handle);
    if (viewIt == handleMap->end()) {
        return nullptr;
    } else {
        return viewIt->second;
    }
}
