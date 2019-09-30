/* global window */
/* eslint no-underscore-dangle: ["error", { "allow": ["__GLESManagerBinding"] }] */

interface GLESManagerBinding {
  createRenderer: <T extends NativeGLESScene>(sceneName: string) => T
  destroyRenderer: (scene: NativeGLESScene) => void
}

declare global {
  interface Window {
    __GLESManagerBinding: GLESManagerBinding;
  }
}

export interface NativeGLESScene {
  handle: () => number
}

function createScene<T extends NativeGLESScene>(sceneName: string): T {
  if (!window.__GLESManagerBinding) {
    throw new Error("__GLESManagerBinding is undefined, cannot create scene")
  }
  return window.__GLESManagerBinding.createRenderer(sceneName);
}

function destroyScene(scene: NativeGLESScene) {
  if (!window.__GLESManagerBinding) {
    throw new Error("__GLESManagerBinding is undefined, cannot create scene")
  }
  window.__GLESManagerBinding.destroyRenderer(scene);
}

export default abstract class GLESScene<T extends NativeGLESScene = NativeGLESScene> {
  protected readonly nativeScene: T

  private bridgeHandle: number

  constructor() {
    this.nativeScene = createScene<T>(this.nativeSceneName())
    this.bridgeHandle = this.nativeScene.handle()
  }

  abstract nativeSceneName(): string;

  public handle() {
    return this.bridgeHandle
  }

  public destroy() {
    destroyScene(this.nativeScene)
    this.bridgeHandle = -1
  }
}
