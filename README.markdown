# system-ifaddrs !(https://secure.travis-ci.org/bbcoimbra/system-getifaddrs.png)[https://secure.travis-ci.org/bbcoimbra/system-getifaddrs.png]

This lib is a wrapper for get\_ifaddrs C routine.

The original routine returns a linked list that contains avaliable inet interfaces.
This lib walks on list and return an hash that contains the interface names and sub-hashes with respectives ip addresses and netmasks.

## Example

Supose that /sbin/ifconfig returns:

```bash
lo  Link encap:Local Loopback
    inet addr:127.0.0.1  Mask:255.0.0.0
    inet6 addr: ::1/128 Scope:Host
    UP LOOPBACK RUNNING  MTU:16436  Metric:1
    RX packets:86688 errors:0 dropped:0 overruns:0 frame:0
    TX packets:86688 errors:0 dropped:0 overruns:0 carrier:0
    collisions:0 txqueuelen:0
    RX bytes:10903658 (10.3 MiB)  TX bytes:10903658 (10.3 MiB)
```

Consider test.rb below:

```ruby
# test.rb
require "pp"
require "system/getifaddrs"
pp System.get_ifaddrs
```

When test.rb is executed:

```bash
$ ruby test.rb
```

Should return:

```ruby
{:lo=>{:inet_addr=>"127.0.0.1", :netmask=>"255.0.0.0"}}
```

## Copyright

Copyright (c) 2010 Bruno Coimbra. See LICENSE for details.
