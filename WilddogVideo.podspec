Pod::Spec.new do |s|
  s.name         = "WilddogVideo"
  s.version      = "0.2.4"
  s.summary      = "The video module let you use wilddog to make realtime media communication."

  s.description  = <<-DESC
The video module let you use wilddog to make realtime media communication.
                   DESC

  s.homepage     = "http://www.wilddog.com/"
  s.license      = "Copyright"
  s.author       = "Wilddog Team"
  s.platform     = :ios, "8.0"

  s.source       = { :http => "https://cdn.wilddog.com/sdk/ios/0.2.4/WilddogVideo-iOS-0.2.4.zip" }
  s.vendored_frameworks = "WebRTC.framework", "WilddogVideo.framework"
  s.frameworks   = "AudioToolbox", "VideoToolbox", "AVFoundation", "GLKit", "CoreMedia", "UIKit", "Foundation", "WebRTC"
  s.library      = "c++"
  s.xcconfig     = { "OTHER_LDFLAGS" => "-ObjC" }

  s.dependency "Wilddog/Sync", "~> 2.0.1"
  s.dependency "Wilddog/Auth", "~> 2.0.1"
end
