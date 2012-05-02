begin
  require File.join(File.dirname(__FILE__), 'rb_getifaddrs')
rescue LoadError
  require File.join(File.dirname(__FILE__), '..', 'rb_getifaddrs')
end