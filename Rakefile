require 'bundler'
Bundler::GemHelper.install_tasks

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new(:spec)

require 'rake/extensiontask'
Rake::ExtensionTask.new('rb_getifaddrs')

task :default => [:compile, :spec]
