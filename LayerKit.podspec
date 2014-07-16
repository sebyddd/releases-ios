Pod::Spec.new do |s|
  s.name          = "LayerKit"
  s.version       = "0.7.3"
  s.summary       = "LayerKit is the iOS client interface for the Layer communications cloud."
  s.license       = {:type=>"Commercial"}
  s.authors       = {"Blake Watters"=>"blake@layer.com", "Klemen Verdnik"=>"klemen@layer.com"}
  s.homepage      = "https://github.com/layerhq/LayerKit"
  s.source        = {:git=>"git@github.com:layerhq/LayerKit-Distribution.git", :tag=>"v0.7.3"}

  s.ios.platform             = :ios, '7.0'
  s.ios.preserve_paths       = 'LayerKit.framework'
  s.ios.public_header_files  = 'LayerKit.framework/Versions/A/Headers/*.h'
  s.ios.resource            = 'LayerKit.framework/Versions/A/Resources/layer-client-messaging-schema.bundle'
  s.ios.vendored_frameworks  = 'LayerKit.framework'
end
