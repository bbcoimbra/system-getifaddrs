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
	if(getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
			netmask, NI_MAXHOST,
			NULL, 0, NI_NUMERICHOST))
		return 0;
	return 1;
}

VALUE rb_get_ifaddrs(void)
{
    struct ifaddrs *ifaddr, *ifa;
    char *str_inet_name = "inet_addr";
    char *str_netmask_name = "netmask";
    VALUE rb_if_hash;

    if (getifaddrs(&ifaddr) == -1)
    {
        rb_raise(rb_eSystemCallError, "Can't get info about interfaces");
    }
    rb_if_hash = rb_hash_new();
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        int family;

        family = get_if_family(ifa);
        if (family == AF_INET)
        {
            VALUE rb_if_data_hash;
            char host[NI_MAXHOST];
            char netmask[NI_MAXHOST];
            char *if_name;
            int s;

            if_name = get_if_name(ifa);
						if_host = malloc(sizeof(char) * NI_MAXHOST);
						if (! get_if_host(ifa, if_host))
							rb_raise(rb_eSystemCallError, "Can't get IP from %s", if_name);

						if_netmask = malloc(sizeof(char) * NI_MAXHOST);
						if (! get_if_netmask(ifa, if_netmask))
							rb_raise(rb_eSystemCallError, "Can't get IP from %s", if_name);

						set_if_hash(rb_if_hash, if_name, if_host, if_netmask);
            rb_if_data_hash = rb_hash_new();
            rb_hash_aset(rb_if_hash,
                         rb_str_intern(rb_str_new2(if_name)),
                         rb_if_data_hash);
            rb_hash_aset(rb_if_data_hash,
                         rb_str_intern(rb_str_new2(str_inet_name)),
                         rb_str_new2(host));
            rb_hash_aset(rb_if_data_hash,
                         rb_str_intern(rb_str_new2(str_netmask_name)),
                         rb_str_new2(netmask));
        }
    }
    freeifaddrs(ifaddr);
    return rb_if_hash;
}

VALUE mSystem;
void Init_rb_getifaddrs(){
    mSystem = rb_define_module("System");
    rb_define_module_function(mSystem, "get_ifaddrs", rb_get_ifaddrs, 0);
}

