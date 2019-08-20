require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

folly_compiler_flags = '-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1 -Wno-comma -Wno-shorten-64-to-32'
folly_version = '2018.10.22.00'
boost_compiler_flags = '-Wno-documentation'

Pod::Spec.new do |s|
  s.name         = "react-native-gles"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.description  = <<-DESC
                  react-native-gles
                   DESC
  s.homepage     = "https://github.com/akshetpandey/react-native-gles"
  s.license      = "MIT"
  s.authors      = { "Akshet Pandey" => "github@akshetpandey.com" }
  s.platform     = :ios, "9.0"
  s.source       = { :git => "https://github.com/akshetpandey/react-native-gles.git", :tag => "#{s.version}" }

  s.source_files = "{ios,cpp}/**/*.{h,hpp,m,mm,c,cpp,swift}"
  s.requires_arc = true

  s.compiler_flags         = folly_compiler_flags + ' ' + boost_compiler_flags
  s.pod_target_xcconfig    = { "HEADER_SEARCH_PATHS" => "\"$(PODS_ROOT)/boost-for-react-native\" \"$(PODS_ROOT)/Folly\" \"$(PODS_ROOT)/DoubleConversion\" \"$(PODS_ROOT)/Headers/Private/React-Core\" \"$(PODS_ROOT)/Headers/Private/React-turbomodule-core\" \"$(PODS_ROOT)/Headers/Private/React-jscallinvoker\"",
                               "USE_HEADERMAP" => "YES",
                               "CLANG_CXX_LANGUAGE_STANDARD" => "c++14" }

  s.framework    = "GLKit"

  s.dependency "React"
end
