require 'ipaddr'
begin
  require File.join(File.dirname(__FILE__), 'rb_getifaddrs')
rescue LoadError
  require File.join(File.dirname(__FILE__), '..', 'rb_getifaddrs')
end

module System
  def self.get_ifaddrs
    get_all_ifaddrs.each_with_object({}) do |data, hash|
      if data[:inet_addr].ipv4?
        hash[data[:interface].to_sym] = {inet_addr: data[:inet_addr].to_s, netmask: data[:netmask].to_s}
      end
    end
  end
end
