require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

def get_interfaces_from_ifconfig
    str = `/sbin/ifconfig`
    ary = str.split("\n\n")
    ary.map!{|e| e.split("\n")}
    ifs = Hash.new{|v| v = Array.new}
    ary.each do |elem|
        elem.map!{|e| e.squeeze(' ').strip}
    end
    ary.each do |elem|
        key = elem.first.split(' ').first
        ifs[key.to_sym] = elem.select{|e| e =~ /inet addr:/}
    end
    interfaces = {}
    ifs.each_pair do |key,value|
        unless value.empty?
            value.first.gsub!('inet addr:','inet_addr:')
            ary = value.first.split(' ')
            temp_hash = {}
            ary.each do |elem|
                k, v = elem.split(':')
                case k
                when 'Mask'
                    k = 'netmask'
                when 'Bcast'
                    k = 'broadcast'
                end
                temp_hash[k.to_sym] = v
            end
            interfaces[key] = temp_hash
        end
    end
    interfaces
end


describe System do

    context "getifaddrs" do
        before :all do
            @ifconfig_interfaces = get_interfaces_from_ifconfig
            @get_ifaddrs_interfaces = System.get_ifaddrs
        end

        it 'should return a hash' do
            @get_ifaddrs_interfaces.should be_kind_of(Hash)
        end

        it 'should have same number of interfaces than system' do
            @get_ifaddrs_interfaces.keys.size.should have_at_least(@ifconfig_interfaces.keys.size).elements
        end

        it 'should have same interfaces than system' do
            @ifconfig_interfaces.keys.each do |k|
                @get_ifaddrs_interfaces.should include(k)
            end
        end
    end
end
