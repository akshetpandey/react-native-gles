//
//  RNGLESView.h
//  RNGLESView
//
//  Created by Akshet Pandey on 8/6/19.
//  Copyright © 2019. All rights reserved.
//

#import <GLKit/GLKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RNGLESView : GLKView

@property (readwrite, nonatomic, assign) int64_t handle;

@end

NS_ASSUME_NONNULL_END
