//
//  RNGLESView.m
//  RNGLESView
//
//  Created by Akshet Pandey on 8/6/19.
//  Copyright © 2019. All rights reserved.
//

#import "RNGLESView.h"

#import <React/RCTViewManager.h>

#import "GLESView.hpp"

@implementation RNGLESView {
    BOOL _needsDisplay;
    std::unique_ptr<GLESView> _nativeView;
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
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(update:)];
        [_displayLink addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
        
        _needsDisplay = YES;
    }
    return self;
}

- (void)removeFromSuperview {
    [self.displayLink invalidate];
    self.displayLink = nil;
    
    [super removeFromSuperview];
}

- (void)setViewName:(NSString *)viewName {
    _needsDisplay = YES;
    _nativeView = GLESViewFactory::createView([viewName cStringUsingEncoding:NSUTF8StringEncoding]);
    _viewName = viewName;
}

- (void)update:(CADisplayLink *)displayLink {
    if (_nativeView) {
        _needsDisplay = _needsDisplay | _nativeView->update(displayLink.timestamp);
        if (_needsDisplay) {
            _needsDisplay = NO;
            [self setNeedsDisplay];
        }
    }
}

- (void)drawRect:(CGRect)rect {
    if (_nativeView) {
        _nativeView->draw();
    }
}

@end

