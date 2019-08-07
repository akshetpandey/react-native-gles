import React from 'react';
import { View, requireNativeComponent } from 'react-native';

export class GLESView extends React.Component {
    render() {
        const {viewName, ...rest} = this.props
        return (
            <View {...rest}>
                <GLESView.RNGLESView style={{ flex: 1 }} viewName={viewName} />
            </View>
        )
    }

    static RNGLESView = requireNativeComponent('RNGLESView', GLESView);
}

export default GLESView;
