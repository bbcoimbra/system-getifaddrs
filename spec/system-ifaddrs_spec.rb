require File.expand_path(File.dirname(__FILE__) + '/spec_helper')

def get_ifs_conf

    ifs = `/sbin/ifconfig`
    ifs = ifs.split("\n\n")
    ifs.map!{|e| e.split("\n")}
    ifs.each do |elem|
        elem.map! do |e|
            e.squeeze(" ").strip
        end
    end
    ifs


end


describe SystemIfaddrs do



end
