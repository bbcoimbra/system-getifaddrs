require 'rubygems'
require 'rake'

begin
  require 'jeweler'
  Jeweler::Tasks.new do |gem|
    gem.name = "system-getifaddrs"
    gem.summary = %Q{This lib is a wrapper for get_ifaddrs C routine}
    gem.description = %Q{This lib is a wrapper for get_ifaddrs C routine. The original routine returns a linked list that contains avaliable inet interfaces. This lib walks on list and return an hash that contains the interface names and sub-hashes with respectives ip addresses and netmasks.}
    gem.email = "bbcoimbra@gmail.com"
    gem.homepage = "http://github.com/bbcoimbra/system-getifaddrs"
    gem.authors = ["Bruno Coimbra"]
    gem.add_development_dependency "rspec"
    gem.extensions << 'ext/rb_getifaddrs/extconf.rb'
    # gem is a Gem::Specification... see http://www.rubygems.org/read/chapter/20 for additional settings
  end
rescue LoadError
  puts "Jeweler (or a dependency) not available. Install it with: sudo gem install jeweler"
end

require 'spec/rake/spectask'
Spec::Rake::SpecTask.new(:spec) do |spec|
  spec.libs << 'lib' << 'spec'
  spec.spec_files = FileList['spec/**/*_spec.rb']
end

Spec::Rake::SpecTask.new(:rcov) do |spec|
  spec.libs << 'lib' << 'spec'
  spec.pattern = 'spec/**/*_spec.rb'
  spec.rcov = true
end

task :spec => [:check_dependencies, :build_ext]

task :default => :spec

require 'rake/rdoctask'
Rake::RDocTask.new do |rdoc|
  if File.exist?('VERSION')
    version = File.read('VERSION')
  else
    version = ""
  end

  rdoc.rdoc_dir = 'rdoc'
  rdoc.title = "system-ifaddrs #{version}"
  rdoc.rdoc_files.include('README*')
  rdoc.rdoc_files.include('lib/**/*.rb')
end


task :clean_ext_objects do
  for ext in %w(rb_getifaddrs) do
    rm "lib/#{ext}.so"
    sh "( cd ext/#{ext}_api && make distclean )"
  end
end

task :build_ext do
  for ext in %w(rb_getifaddrs) do
    sh "( cd ext/#{ext}_api && ruby extconf.rb && make )"
    cp "ext/#{ext}_api/#{ext}.so", 'lib/'
  end
end
