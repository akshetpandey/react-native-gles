//
// Created by Akshet Pandey on 2019-08-02.
//

#include "GLESViewJNI.h"
#include "GLESViewFactory.hpp"

const double NANO_SECONDS_IN_SECONDS = 1000000000.0;

GLESViewJNI::GLESViewJNI(JNIEnv *env, jobject thiz) {
    _weakJavaPeer = env->NewWeakGlobalRef(thiz);
}

void GLESViewJNI::destroy(JNIEnv *env) {
    env->DeleteWeakGlobalRef(_weakJavaPeer);
    destroyGL();
    _nativeView = nullptr;
}

void GLESViewJNI::setView(std::string view) {
    _renderMutex.lock();
    _didInitialize = false;
    if(_nativeView) {
        _nativeView->destroyGL();
    }
    _nativeView = GLESViewFactory::createView(view);
    _renderMutex.unlock();
}

void GLESViewJNI::initializeGL() {
    _renderMutex.lock();
    if (!_didInitialize && _nativeView) {
        _nativeView->initializeGL();
        _didInitialize = true;
    }
    _renderMutex.unlock();
}

void GLESViewJNI::destroyGL() {
    _renderMutex.lock();
    _didInitialize = false;
    if (_nativeView) {
        _nativeView->destroyGL();
    }
    _renderMutex.unlock();
}

bool GLESViewJNI::update(int64_t frameTimeNanos) {
    bool shouldUpdate = false;
    _renderMutex.lock();
    if (_didInitialize && _nativeView) {
        shouldUpdate = _nativeView->update(frameTimeNanos/NANO_SECONDS_IN_SECONDS);
    } else {
        shouldUpdate = true;
    }
    _renderMutex.unlock();
    return shouldUpdate;
}

void GLESViewJNI::draw() {
    initializeGL();
    _renderMutex.lock();
    if (_didInitialize && _nativeView) {
        _nativeView->draw();
    }
    _renderMutex.unlock();
}

extern "C" {

JNIEXPORT jlong JNICALL
Java_com_akshetpandey_rnglesview_RNGLESView_initialize(
        JNIEnv *env, jobject instance) {
    auto peer = new GLESViewJNI(env, instance);
    return (jlong) peer;
}

JNIEXPORT void JNICALL
Java_com_akshetpandey_rnglesview_RNGLESView_initializeGL(
        JNIEnv *env, jobject instance, jlong nativePeer) {
    auto peer = (GLESViewJNI *) nativePeer;
    peer->initializeGL();
}

JNIEXPORT void JNICALL
Java_com_akshetpandey_rnglesview_RNGLESView_destroy(
        JNIEnv *env, jobject instance, jlong nativePeer) {
    auto peer = (GLESViewJNI *) nativePeer;
    peer->destroy(env);
    delete peer;
}

JNIEXPORT jboolean JNICALL
Java_com_akshetpandey_rnglesview_RNGLESView_nativeUpdate(
        JNIEnv *env, jobject instance, jlong nativePeer, jlong frameTimeNanos) {
    auto peer = (GLESViewJNI *) nativePeer;
    return (jboolean) peer->update(frameTimeNanos);
}

JNIEXPORT void JNICALL
Java_com_akshetpandey_rnglesview_RNGLESView_nativeOnDrawFrame(
        JNIEnv *env, jobject instance, jlong nativePeer) {
    auto peer = (GLESViewJNI *)nativePeer;
    peer->draw();
}

JNIEXPORT void JNICALL
Java_com_akshetpandey_rnglesview_RNGLESView_nativeSetView(
        JNIEnv *env, jobject instance, jlong nativePeer, jstring view) {
    auto peer = (GLESViewJNI *)nativePeer;
    auto cStringView = env->GetStringUTFChars(view, nullptr);
    peer->setView(cStringView);
    env->ReleaseStringUTFChars(view, cStringView);
}

}
