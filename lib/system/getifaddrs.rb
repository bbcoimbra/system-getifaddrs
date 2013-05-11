begin
  require File.join(File.dirname(__FILE__), 'rb_getifaddrs')
rescue LoadError
  require File.join(File.dirname(__FILE__), '..', 'rb_getifaddrs')
end

module System
  def self.get_ifaddrs
    get_all_ifaddrs.each_with_object({}) do |data, hash|
      hash[data[:interface].to_sym] = {inet_addr: data[:inet_addr], netmask: data[:netmask]}
    end
  end
end
