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
                temp_hash[k.downcase.to_sym] = v
            end
            interfaces[key] = temp_hash
        end
    end
    interfaces
end


describe System do

    context "ifadds" do
        before :all do
            @interfaces = get_interfaces_from_ifconfig
        end

        it 'should return a hash' do
            System.get_ifaddrs.should be_kind_of(Hash)
        end

        it 'should have same number of interfaces than system' do
            System.get_ifaddrs.should have_at_least(@interfaces).elements
        end

        it 'should have same interfaces than system' do
            pending
            System.get_ifaddrs.keys.sort.should == @interfaces.keys.sort
        end
    end
end
