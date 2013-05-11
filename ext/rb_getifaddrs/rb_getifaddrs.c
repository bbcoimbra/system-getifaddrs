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

char * get_if_name(struct ifaddrs *ifa){
	return ifa->ifa_name;
}

int get_if_host(struct ifaddrs *ifa, char *host){
	if(getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
			host, NI_MAXHOST,
			NULL, 0, NI_NUMERICHOST))
		return 0;
	return 1;
}

int get_if_netmask(struct ifaddrs *ifa, char *netmask){
	if(getnameinfo(ifa->ifa_netmask, sizeof(struct sockaddr_in),
			netmask, NI_MAXHOST,
			NULL, 0, NI_NUMERICHOST))
		return 0;
	return 1;
}

VALUE if_hash(struct ifaddrs *ifa)
{
    VALUE hash = rb_hash_new();

    char *if_host, *if_netmask, *if_name;

    if_name = get_if_name(ifa);
    if_host = malloc(sizeof(char) * NI_MAXHOST);
    if_netmask = malloc(sizeof(char) * NI_MAXHOST);

    rb_hash_aset(hash, ID2SYM(rb_intern("interface")), rb_str_new2(if_name));

    if (get_if_host(ifa, if_host))
       rb_hash_aset(hash, ID2SYM(rb_intern("inet_addr")), rb_str_new2(if_host));
    else
       rb_raise(rb_eSystemCallError, "Can't get IP from %s", if_name);

    if (get_if_netmask(ifa, if_netmask))
       rb_hash_aset(hash, ID2SYM(rb_intern("netmask")), rb_str_new2(if_netmask));
    else
       rb_raise(rb_eSystemCallError, "Can't get netmask from %s", if_name);

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
        if (family == AF_INET)
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

