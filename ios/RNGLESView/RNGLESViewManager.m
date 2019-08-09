//
//  RNGLViewManager.m
//  RNGLESView
//
//  Created by Akshet Pandey on 7/29/19.
//  Copyright © 2019. All rights reserved.
//

#import "RNGLESViewManager.h"

#import "RNGLESView.h"
#import "RNGLESContextManager.h"

@implementation RNGLESViewManager

RCT_EXPORT_MODULE(RNGLESView)

RCT_EXPORT_VIEW_PROPERTY(viewName, NSString *)

- (UIView *)view {
    RNGLESContextManager *contextManager = [RNGLESContextManager sharedInstance];
    RNGLESView *view = [[RNGLESView alloc] initWithFrame:CGRectZero context:contextManager.contextForRendering];
    return view;
}

@end
