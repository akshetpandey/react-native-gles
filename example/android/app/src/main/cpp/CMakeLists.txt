# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions -std=c++14 -Wno-deprecated-declarations -Wno-reorder -Wno-invalid-offsetof -fPIC -unresolved-symbols=ignore-in-shared-libs")
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(repoROOT_DIR ../../../../..)
set(rnglesview_DIR ${repoROOT_DIR}/..)

# Add source files to be compliled here
# Path is relative to this CMakeLists.txt file
set(SOURCE_FILES
        ${repoROOT_DIR}/cpp/TeapotScene.cpp
        ${repoROOT_DIR}/cpp/TeapotRenderer/teapot.inl
        ${repoROOT_DIR}/cpp/TeapotRenderer/Shaders/ShaderPlain.fsh
        ${repoROOT_DIR}/cpp/TeapotRenderer/Shaders/VS_ShaderPlain.vsh
        ${repoROOT_DIR}/cpp/TeapotRenderer/TeapotRenderer.cpp
        ${repoROOT_DIR}/cpp/NDKHelper/interpolator.cpp
        ${repoROOT_DIR}/cpp/NDKHelper/tapCamera.cpp
        ${repoROOT_DIR}/cpp/NDKHelper/shader.cpp
        ${repoROOT_DIR}/cpp/NDKHelper/vecmath.cpp
        )

# Specifies a path to native header files.
# Path is relative to this CMakeLists.txt file
include_directories(${repoROOT_DIR}/cpp/)
include_directories(${repoROOT_DIR}/cpp/NDKHelper/)
include_directories(${repoROOT_DIR}/cpp/TeapotRenderer/)

include_directories(${rnglesview_DIR}/cpp/)

add_subdirectory(${rnglesview_DIR}/android/src/main/cpp ./../../../.externalNativeBuild/rnglesviewNativeBuildDir)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
add_library(
        # Specifies the name of the library.
        exampleNative

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${SOURCE_FILES}
        $<TARGET_OBJECTS:rnglesviewNative>)

#add_library(rnglesviewNative-lib SHARED IMPORTED)
#
#set(distribution_DIR ${rnglesview_DIR}/android/build/outputs/aar/android-debug/jni/)
#
#set_target_properties(rnglesviewNative-lib PROPERTIES IMPORTED_LOCATION
#        ${distribution_DIR}/debug/${ANDROID_ABI}/librnglesviewNative.so)
#

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

find_library( # Sets the name of the path variable.
        glesv2-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        GLESv2)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        exampleNative

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${glesv2-lib}
        ${rnglesviewNative-lib})
