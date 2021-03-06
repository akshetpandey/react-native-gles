//
// Created by Akshet Pandey on 2019-08-02.
//

#pragma once

#include <string>

#include <jni.h>
#include <mutex>

#include "GLESView.hpp"

class GLESViewJNI {
public:
    GLESViewJNI(JNIEnv *env, jobject thiz);
    ~GLESViewJNI() = default;

    void setView(std::string view);
    void initializeGL();
    void destroyGL();
    void draw();
    bool update(int64_t frameTimeNanos);

    void destroy(JNIEnv *env);
private:
    std::unique_ptr<GLESView> _nativeView;
    bool _didInitialize;
    std::mutex _renderMutex;
    jweak _weakJavaPeer;
};
