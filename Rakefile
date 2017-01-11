require "rake/extensiontask"

spec = Gem::Specification.new do |s|
  s.name = "tm1638"
  s.version     = '0.1.0'
  s.licenses    = ['MIT']
  s.summary     = "A ruby gem for the tm1638 display on raspberry pi"
  s.description = "Install http://www.airspayce.com/mikem/bcm2835/index.html and https://github.com/mjoldfield/pi-tm1638/blob/master/src/tm1638.c first"
  s.authors     = ["Rick Pannen"]
  s.email       = 'pannen@gmail.com'
  s.homepage    = 'https://github.com/RickP/tm1638_gem'
  s.files       = %w[ext/tm1638/tm1638.c]
  s.extensions  = %w[ext/tm1638/extconf.rb]
end

Gem::PackageTask.new(spec) do |pkg|
end

Rake::ExtensionTask.new("tm1638", spec) do |ext|
  ext.lib_dir = "ext/tm1638"
end
