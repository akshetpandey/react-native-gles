# react-native-gles

## Getting started

`$ npm install react-native-gles --save`

### Mostly automatic installation

`$ react-native link react-native-gles`

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-gles` and add `RNGLESView.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNGLESView.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainApplication.java`
  - Add `import com.akshetpandey.rnglesview.RNGLESViewPackage;` to the imports at the top of the file
  - Add `new RNGLESViewPackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-gles'
  	project(':react-native-gles').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-gles/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-gles')
  	```


## Usage
```javascript
import RNGLESView from 'react-native-gles';

// TODO: What to do with the module?
RNGLESView;
```
