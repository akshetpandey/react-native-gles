import React from 'react';
import { ViewProps, View, requireNativeComponent } from 'react-native';

interface GLESViewProps extends ViewProps {
  viewName: string;
}

export default class GLESView extends React.Component<GLESViewProps> {
  static RNGLESView = requireNativeComponent('RNGLESView');

  render() {
    const { viewName, ...rest } = this.props;
    return (
      <View {...rest}>
        <GLESView.RNGLESView style={{ flex: 1 }} viewName={viewName} />
      </View>
    );
  }
}
