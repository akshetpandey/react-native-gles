//
//  RNGLESContextManager.m
//  RNGLESView
//
//  Created by Akshet Pandey on 8/8/19.
//  Copyright © 2019 Facebook. All rights reserved.
//

#import "RNGLESContextManager.h"

@implementation RNGLESContextManager {
    EAGLContext *_rootContext;
    EAGLContext *_renderingContext;
}

+ (RNGLESContextManager *)sharedInstance {
    static dispatch_once_t onceToken;
    static RNGLESContextManager *instance;
    dispatch_once(&onceToken, ^{
        instance = [[RNGLESContextManager alloc] init];
    });
    return instance;
}

- (instancetype)init {
    if (self = [super init]) {
        _rootContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        _renderingContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 sharegroup:_rootContext.sharegroup];
    }
    return self;
}

- (EAGLContext *)contextForRendering {
    return _renderingContext;
}

- (EAGLContext *)contextForBackgroundProcessing {
    return _rootContext;
}

- (void)dispatchAsyncInGLLoaderThread:(glLoaderBlock)block {
    dispatch_async(glLoaderQueue(), ^{
        [EAGLContext setCurrentContext:self.contextForBackgroundProcessing];
        block();
    });
}

dispatch_queue_t glLoaderQueue() {
    static dispatch_once_t queueCreationGuard;
    static dispatch_queue_t queue;
    dispatch_once(&queueCreationGuard, ^{
        queue = dispatch_queue_create("com.rnglesview.glLoaderQueue", 0);
    });
    return queue;
}

@end
