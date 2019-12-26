/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "AppDelegate.h"

#import <jsi/jsi.h>

#import <React/RCTBridge.h>
#import <React/RCTBridge+Private.h>
#import <React/RCTBridgeDelegate.h>
#import <React/RCTCxxBridgeDelegate.h>
#import <React/RCTBundleURLProvider.h>
#import <React/RCTRootView.h>
#import <cxxreact/JSExecutor.h>

#import "GLESManager.hpp"

@interface RCTCxxBridge ()
- (void)invokeAsync:(std::function<void()>&&)func;
@end

@interface AppDelegate () <RCTBridgeDelegate, RCTCxxBridgeDelegate>
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  RCTBridge *bridge = [[RCTBridge alloc] initWithDelegate:self launchOptions:launchOptions];
  RCTRootView *rootView = [[RCTRootView alloc] initWithBridge:bridge
                                                   moduleName:@"example"
                                            initialProperties:nil];

  rootView.backgroundColor = [[UIColor alloc] initWithRed:1.0f green:1.0f blue:1.0f alpha:1];

  self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
  UIViewController *rootViewController = [UIViewController new];
  rootViewController.view = rootView;
  self.window.rootViewController = rootViewController;
  [self.window makeKeyAndVisible];
  return YES;
}

- (NSURL *)sourceURLForBridge:(RCTBridge *)bridge
{
#if DEBUG
  return [[RCTBundleURLProvider sharedSettings] jsBundleURLForBundleRoot:@"index" fallbackResource:nil];
#else
  return [[NSBundle mainBundle] URLForResource:@"main" withExtension:@"jsbundle"];
#endif
}

- (std::unique_ptr<facebook::react::JSExecutorFactory>)jsExecutorFactoryForBridge:(RCTBridge *)bridge {
  auto cxxBridge = (RCTCxxBridge *)bridge;
  [cxxBridge invokeAsync:[cxxBridge]() {
    auto runtime = (facebook::jsi::Runtime *)cxxBridge.runtime;
    auto glesManagerBinding = std::make_shared<GLESManagerBinding>();
    GLESManagerBinding::install(*runtime, glesManagerBinding);
  }];
  return NULL;
}

@end
