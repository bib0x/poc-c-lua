#ifndef __CFUNCTIONS__
#define __CFUNCTIONS__

#include <net/if.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <lauxlib.h>

static int l_print_ifaces(lua_State* L);
int luaopen_cfunctions(lua_State* L);

#include <sys/types.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <netdb.h>

static int l_network_info_ret(lua_State* L);

#endif
