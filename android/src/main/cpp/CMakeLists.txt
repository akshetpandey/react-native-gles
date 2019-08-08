# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions -std=c++14 -Wno-deprecated-declarations -Wno-reorder -Wno-invalid-offsetof -fPIC")

# Add source files to be compliled here
# Path is relative to this CMakeLists.txt file
set(SOURCE_FILES
        GLESViewJNI.cpp
        ../../../../cpp/GLESView.cpp
        ../../../../cpp/GLESViewFactory.cpp
        )

# Specifies a path to native header files.
# Path is relative to this CMakeLists.txt file
include_directories(includes/)
include_directories(../../../../cpp/)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
add_library(
        # Specifies the name of the library.
        rnglesviewNative

        # Sets the library as a shared library.
        OBJECT

        # Provides a relative path to your source file(s).
        ${SOURCE_FILES}
)
