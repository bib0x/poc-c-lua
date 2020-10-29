#include "cfunctions.h"

// Declare functions for registration
static const struct luaL_reg cfunctions[] = {
    {"print_ifaces", l_print_ifaces},
    {"get_network_info_ret", l_network_info_ret},
    {NULL, NULL}
};

// C function
// Print information from C
static int l_print_ifaces(lua_State* L) {
    struct if_nameindex *if_nidxs;
    struct if_nameindex *intf;

    if_nidxs = if_nameindex();
    if (if_nidxs != NULL) {
        for (intf = if_nidxs; intf->if_index != 0 || intf->if_name != NULL; intf++) {
            printf("%s\n", intf->if_name);
        }
        if_freenameindex(if_nidxs);
    }
    return 0;
}

// Get IP address from interface name (as parameter)
static int l_network_info_ret(lua_State* L) {
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];

    // Get first argument
    const char *interface = luaL_checkstring(L, 1);
   
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return -1;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (!strcmp(ifa->ifa_name, interface)) {
            if (ifa->ifa_addr != NULL) {
                int family = ifa->ifa_addr->sa_family;

                if (family == AF_INET) {
                    if (!getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) {
                        // Push return value
                        lua_pushstring(L, host);
                        freeifaddrs(ifaddr);
                        return 1;
                    }
                }
            } 
        }
    }
    // Push return value
    lua_pushstring(L, NULL);
    freeifaddrs(ifaddr);
    return 1;
}

// Register functions
int luaopen_cfunctions(lua_State* L) {
    luaL_openlib(L, "cfunctions", cfunctions, 0);
    return 1;
}
