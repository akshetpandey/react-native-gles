//
//  RNGLESView.m
//  RNGLESView
//
//  Created by Akshet Pandey on 8/6/19.
//  Copyright © 2019. All rights reserved.
//

#import "RNGLESView.h"

#import <mutex>

#import <React/RCTViewManager.h>

#import "RNGLESContextManager.h"

#import "GLESView.hpp"
#import "GLESViewFactory.hpp"

@implementation RNGLESView {
    CADisplayLink *_displayLink;
    std::unique_ptr<GLESView> _nativeView;
    std::mutex _renderMutex;
    std::atomic_bool _didInitialize;
}

- (instancetype)initWithFrame:(CGRect)frame context:(EAGLContext *)context {
    if (self = [super initWithFrame:frame context:context]) {
        self.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
        self.drawableDepthFormat = GLKViewDrawableDepthFormat16;
        self.drawableStencilFormat = GLKViewDrawableStencilFormat8;
        self.drawableMultisample = GLKViewDrawableMultisampleNone;
        self.contentScaleFactor = RCTScreenScale();
        self.opaque = NO;
        self.backgroundColor = [UIColor clearColor];
    }
    return self;
}

- (void)dealloc {
    if (_displayLink) {
        [_displayLink invalidate];
        _displayLink = nil;
    }

    if (_nativeView) {
        auto oldView = _nativeView.release();
        RNGLESContextManager *contextManager = [RNGLESContextManager sharedInstance];
        [contextManager dispatchAsyncInGLLoaderThread:^{
            oldView->destroyGL();
            delete oldView;
        }];
    }
}

- (void)willMoveToWindow:(nullable UIWindow *)newWindow {
    [super willMoveToWindow:newWindow];

    if (_displayLink) {
        [_displayLink invalidate];
        _displayLink = nil;
    }

    if (newWindow) {
        _displayLink = [newWindow.screen displayLinkWithTarget:self selector:@selector(update:)];
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
    }
}

- (void)setViewName:(NSString *)viewName {
    std::lock_guard<std::mutex> lock(_renderMutex);

    _didInitialize = false;
    if (_nativeView) {
        auto oldView = _nativeView.release();
        RNGLESContextManager *contextManager = [RNGLESContextManager sharedInstance];
        [contextManager dispatchAsyncInGLLoaderThread:^{
            oldView->destroyGL();
            delete oldView;
        }];
    }

    _nativeView = GLESViewFactory::createView([viewName cStringUsingEncoding:NSUTF8StringEncoding]);
    if (_nativeView) {
        // Thread safe because delete is called on the glLoader thread which is serialized
        auto newView = _nativeView.get();
        RNGLESContextManager *contextManager = [RNGLESContextManager sharedInstance];
        [contextManager dispatchAsyncInGLLoaderThread:^{
            newView->initializeGL();
            self->_didInitialize = true;
        }];
    }

    _viewName = viewName;
}

- (void)update:(CADisplayLink *)displayLink {
    std::lock_guard<std::mutex> lock(_renderMutex);
    if (_didInitialize && _nativeView) {
        if (_nativeView->update(displayLink.timestamp)) {
            [self setNeedsDisplay];
        }
    }
}

- (void)drawRect:(CGRect)rect {
    std::lock_guard<std::mutex> lock(_renderMutex);
    if (_didInitialize && _nativeView) {
        _nativeView->draw();
    }
}

@end
