require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "react-native-gles"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.description  = <<-DESC
                  react-native-gles
                   DESC
  s.homepage     = "https://github.com/akshetpandey/react-native-gles"
  s.license      = "MIT"
  # s.license    = { :type => "MIT", :file => "FILE_LICENSE" }
  s.authors      = { "Akshet Pandey" => "github@akshetpandey.com" }
  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/akshetpandey/react-native-gles.git", :tag => "#{s.version}" }

  s.source_files = "{ios,cpp}/**/*.{h,hpp,m,mm,c,cpp,swift}"
  s.requires_arc = true

  s.framework    = "GLKit"

  s.dependency "React"
end

