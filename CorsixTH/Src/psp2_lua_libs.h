#ifndef CORSIX_TH_PSP2_LUA_LIBS_H_
#define CORSIX_TH_PSP2_LUA_LIBS_H_

#include <lua.h>

#ifdef __cplusplus
extern "C" {
#endif

int luaopen_lfs(lua_State *L);
int luaopen_lpeg(lua_State *L);

#ifdef __cplusplus
}
#endif

#endif