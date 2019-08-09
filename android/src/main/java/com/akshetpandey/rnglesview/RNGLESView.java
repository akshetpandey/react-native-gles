package com.akshetpandey.rnglesview;

import android.content.Context;
import android.opengl.GLES20;

import com.facebook.react.modules.core.ChoreographerCompat;
import com.facebook.react.modules.core.ReactChoreographer;
import com.facebook.react.uimanager.ThemedReactContext;

import java.util.concurrent.atomic.AtomicBoolean;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RNGLESView extends GLTextureView implements GLTextureView.Renderer {
  private String viewName;
  private long mNativePeer;
  private AtomicBoolean mPaused = new AtomicBoolean(false);
  private ChoreographerCompat.FrameCallback mFrameCallback;

  public RNGLESView(Context context) {
    super(context);
  }

  public RNGLESView(ThemedReactContext context) {
    super(context);
    mPaused.set(false);
    mNativePeer = initialize();
    mFrameCallback = new ChoreographerCompat.FrameCallback() {
      @Override
      public void doFrame(long frameTimeNanos) {
        RNGLESView.this.doFrame(frameTimeNanos);
      }
    };
    setEGLContextClientVersion(2);
    setOpaque(false);
    setEGLConfigChooser(8,8,8,8,16,8);
    setRenderer(this);
    setRenderMode(GLTextureView.RENDERMODE_WHEN_DIRTY);
    ReactChoreographer choreographer = ReactChoreographer.getInstance();
    choreographer.postFrameCallback(ReactChoreographer.CallbackType.DISPATCH_UI, mFrameCallback);
  }

  public void finalize() throws java.lang.Throwable {
    destroy(mNativePeer);
    super.finalize();
  }

  public void doFrame(long frameTimeNanos) {
    if (mPaused.get()) {
      return;
    }
    if (mNativePeer != 0) {
      if (nativeUpdate(mNativePeer, frameTimeNanos)) {
        requestRender();
      }
    }
    if (!mPaused.get()) {
      ReactChoreographer choreographer = ReactChoreographer.getInstance();
      choreographer.postFrameCallback(ReactChoreographer.CallbackType.DISPATCH_UI, mFrameCallback);
    }
  }

  @Override
  public void onResume() {
    super.onResume();
    mPaused.set(false);
    ReactChoreographer choreographer = ReactChoreographer.getInstance();
    choreographer.postFrameCallback(ReactChoreographer.CallbackType.DISPATCH_UI, mFrameCallback);
  }

  @Override
  public void onPause() {
    super.onPause();
    mPaused.set(true);
  }

  public void setViewName(String viewName) {
    this.viewName = viewName;
    nativeSetView(mNativePeer, viewName);
  }

  public String getViewName() {
    return viewName;
  }

  public void onSurfaceCreated(GL10 unused, EGLConfig config) {
    initializeGL(mNativePeer);
  }

  public void onDrawFrame(GL10 unused) {
    nativeOnDrawFrame(mNativePeer);
  }

  public void onSurfaceChanged(GL10 unused, int width, int height) {
    GLES20.glViewport(0, 0, width, height);
  }

  private native long initialize();
  private native void initializeGL(long nativePeer);
  private native void destroy(long nativePeer);
  private native boolean nativeUpdate(long nativePeer, long frameTimeNanos);
  private native void nativeOnDrawFrame(long nativePeer);
  private native void nativeSetView(long nativePeer, String viewName);
}
