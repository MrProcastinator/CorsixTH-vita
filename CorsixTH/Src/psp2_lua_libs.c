#include "psp2_lua_libs.h"

#include <lua.h>
#include <lauxlib.h>

int lj_cf_print_psp2(lua_State *L);
int lj_cf_error_psp2(lua_State *L);

static const struct luaL_Reg psp2lib [] = {
  {"print", lj_cf_print_psp2},
  {"error", lj_cf_error_psp2},
  {NULL, NULL} /* end of array */
};

int luaopen_psp2(lua_State *L)
{
  luaL_register(L, "psp2", psp2lib);
  return 1;
}