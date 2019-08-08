package com.akshetpandey.rnglesview;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import android.view.View;

import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;
import com.facebook.react.uimanager.annotations.ReactProp;

public class RNGLESViewManager extends SimpleViewManager<View> {

    private static final String REACT_CLASS = "RNGLESView";

    @Override
    @NonNull
    public String getName() {
        return REACT_CLASS;
    }

    @Override
    @NonNull
    public View createViewInstance(@NonNull ThemedReactContext context) {
        return new RNGLESView(context);
    }

  @ReactProp(name = "viewName")
  public void setSrc(RNGLESView view, @Nullable String viewName) {
    view.setViewName(viewName);
  }
}
