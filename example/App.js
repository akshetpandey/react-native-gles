/**
 * Sample React Native App
 *
 * adapted from App.js generated by the following command:
 *
 * react-native init example
 *
 * https://github.com/facebook/react-native
 */

import React, { Component } from 'react';
import { StyleSheet, Text, ImageBackground } from 'react-native';
import GLESView from 'react-native-gles';

export default class App extends Component {
  render() {
    return (
      <ImageBackground
        style={styles.container}
        source={require('./background.png')}
      >
        <Text style={styles.welcome}>RNGLESView example</Text>
        <GLESView
          style={{ width: 200, height: 200, marginTop: 100 }}
          viewName="TeapotScene"
        />
      </ImageBackground>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    width: '100%',
    height: '100%',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
});
