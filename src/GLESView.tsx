/* eslint react/jsx-props-no-spreading: ["error", { "exceptions": ["View"] }] */

import React from 'react';
import { ViewProps, View, requireNativeComponent } from 'react-native';

import GLESScene from './GLESScene';

export interface GLESViewProps extends ViewProps {
  scene: GLESScene;
}

export default class GLESView extends React.PureComponent<GLESViewProps> {
  static RNGLESView = requireNativeComponent('RNGLESView');

  render() {
    const { scene, ...rest } = this.props;
    return (
      <View {...rest}>
        <GLESView.RNGLESView style={{ flex: 1 }} handle={scene.handle()} />
      </View>
    );
  }
}
