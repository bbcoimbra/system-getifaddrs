#include "ruby.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_if_family(struct ifaddrs *ifa){
	if(ifa && ifa->ifa_addr)
		return ifa->ifa_addr->sa_family;
	return 0;
}

VALUE ipaddr(struct sockaddr *ip) {
    VALUE bytes;

    switch(ip->sa_family) {
    case AF_INET:
        bytes = rb_str_new(&((struct sockaddr_in *)ip)->sin_addr.s_addr, 4);
        break;

    case AF_INET6:
        bytes = rb_str_new(&((struct sockaddr_in6 *)ip)->sin6_addr.s6_addr, 16);
        break;

    default:
        rb_raise(rb_eSystemCallError, "Unhandled IP family.");

    }

    VALUE ipaddr = rb_const_get(rb_cObject, rb_intern("IPAddr"));
    return rb_funcall(ipaddr, rb_intern("new_ntoh"), 1, bytes);
}

VALUE if_hash(struct ifaddrs *ifa)
{
    VALUE hash = rb_hash_new();

    rb_hash_aset(hash, ID2SYM(rb_intern("interface")), rb_str_new2(ifa->ifa_name));
    rb_hash_aset(hash, ID2SYM(rb_intern("inet_addr")), ipaddr(ifa->ifa_addr));
    rb_hash_aset(hash, ID2SYM(rb_intern("netmask")), ipaddr(ifa->ifa_netmask));

    return hash;
}

VALUE rb_get_all_ifaddrs(void)
{
    struct ifaddrs *ifaddr, *ifa;
    VALUE rb_if_arr;

    if (getifaddrs(&ifaddr) == -1)
    {
        rb_raise(rb_eSystemCallError, "Can't get info about interfaces");
    }
    rb_if_arr = rb_ary_new();
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        int family;

        family = get_if_family(ifa);
        if (family == AF_INET || family == AF_INET6)
        {
            rb_ary_push(rb_if_arr, if_hash(ifa));
        }
    }

    freeifaddrs(ifaddr);
    return rb_if_arr;
}

VALUE mSystem;
void Init_rb_getifaddrs(){
    mSystem = rb_define_module("System");
    rb_define_module_function(mSystem, "get_all_ifaddrs", rb_get_all_ifaddrs, 0);
}

