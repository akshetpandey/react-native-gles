//
//  RNGLViewManager.m
//  RNGLESView
//
//  Created by Akshet Pandey on 7/29/19.
//  Copyright © 2019. All rights reserved.
//

#import "RNGLESViewManager.h"

#import "RNGLESView.h"

@interface RNGLESViewManager ()

@property (nonatomic, strong) EAGLContext *glContext;

@end

@implementation RNGLESViewManager

RCT_EXPORT_MODULE(RNGLESView)

RCT_EXPORT_VIEW_PROPERTY(viewName, NSString *)

+ (BOOL)requiresMainQueueSetup {
    return YES;
}

- (instancetype)init {
    if (self = [super init]) {
        self.glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    }
    return self;
}

- (UIView *)view {
    return [[RNGLESView alloc] initWithFrame:CGRectZero context:self.glContext];
}

@end
