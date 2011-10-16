require 'bundler'
Bundler::GemHelper.install_tasks

require 'spec/rake/spectask'
Spec::Rake::SpecTask.new

require 'rake/extensiontask'
Rake::ExtensionTask.new('rb_getifaddrs')

task :default => [:compile, :spec]
