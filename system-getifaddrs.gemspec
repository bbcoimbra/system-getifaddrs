# -*- encodign: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)
require "system/getifaddrs/version"

Gem::Specification.new do |s|
  s.name = "system-getifaddrs"
  s.version = System::Getifaddrs::VERSION
  s.platform = Gem::Platform::RUBY
  s.authors = ["Bruno Coimbra"]
  s.email = %q{bbcoimbra@gmail.com}
  s.homepage = %q{http://github.com/bbcoimbra/system-getifaddrs}
  s.summary = %q{This lib is a wrapper for get_ifaddrs C routine}
  s.description = %q{This lib is a wrapper for get_ifaddrs C routine. The original routine returns a linked list that contains avaliable inet interfaces. This lib walks on list and return an hash that contains the interface names and sub-hashes with respectives ip addresses and netmasks.}
  s.add_development_dependency(%q<rspec>, "~> 1.3")
  s.add_development_dependency(%q<rake-compiler>, [">= 0"])
  s.extensions    = `git ls-files -- ext/*`.split("\n").select{|f| f =~ /extconf/}
  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  s.require_paths = ["lib"]
end

