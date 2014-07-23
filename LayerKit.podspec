Pod::Spec.new do |s|
  s.name = 'LayerKit'
  s.version = '0.7.4'
  s.summary = 'LayerKit is the iOS client interface for the Layer communications cloud.'
  s.license = 'Commercial'
  s.authors = {"Blake Watters"=>"blake@layer.com", "Klemen Verdnik"=>"klemen@layer.com"}
  s.homepage = 'https://github.com/layerhq/LayerKit'
  s.source = { git: 'git@github.com:layerhq/releases-ios.git', tag: "v#{s.version}" }
  
  s.ios.frameworks = 'CFNetwork', 'Security', 'MobileCoreServices', 'SystemConfiguration'
  s.libraries = 'z'

  s.platform = :ios, '7.0'
  s.ios.platform             = :ios, '7.0'
  s.ios.preserve_paths       = 'LayerKit.framework'
  s.ios.public_header_files  = 'LayerKit.framework/Versions/A/Headers/*.h'
  s.ios.resource             = 'LayerKit.framework/Versions/A/Resources/**/*'
  s.ios.vendored_frameworks  = 'LayerKit.framework'
end
