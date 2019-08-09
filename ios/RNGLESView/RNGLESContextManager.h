//
//  RNGLESContextManager.h
//  RNGLESView
//
//  Created by Akshet Pandey on 8/8/19.
//  Copyright © 2019 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^glLoaderBlock)(void);

@interface RNGLESContextManager : NSObject

+ (RNGLESContextManager *)sharedInstance;

- (EAGLContext *)contextForRendering;
- (EAGLContext *)contextForBackgroundProcessing;

- (void)dispatchAsyncInGLLoaderThread:(glLoaderBlock)block;

@end

NS_ASSUME_NONNULL_END
