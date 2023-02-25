#include "psp2_output.h"
#include <lua.h>
#include <lauxlib.h>
#include <stdio.h>
#include <string.h>

#define LOG_PATH "ux0:data/corsixth"
#define LOG_STDOUT_PATH LOG_PATH "/stdout.txt"
#define LOG_STDERR_PATH LOG_PATH "/stderr.txt"

FILE* vita_stdout = NULL;
FILE* vita_stderr = NULL;

void load_output_files(FILE** out, FILE** err)
{
    FILE* f;
    if(out != NULL)
    {
        *out = fopen(LOG_STDOUT_PATH, "w");
    }
    if(err != NULL)
    {
        *err = fopen(LOG_STDERR_PATH, "w");
    }
}

static int lj_cf_print_psp2(lua_State *L)
{
  int i, type, size = 0, nargs = lua_gettop(L);
  const char* str = NULL;
  for (i = 0; i < nargs; i++) {
    if (i)
        fputc(' ', vita_stdout);
    type = lua_type(L, i);
    switch(type)
    {
        case LUA_TSTRING:  /* booleans */
          str = lua_tostring(L, i);
          size = strlen(str);
          fwrite(str, 1, size, vita_stdout);
        case LUA_TBOOLEAN:  /* booleans */
          fprintf(vita_stdout, lua_toboolean(L, i) ? "true" : "false");
          break;
        case LUA_TNUMBER:  /* numbers */
          fprintf(vita_stdout, "%g", lua_tonumber(L, i));
          break;
        default:  /* other values */
          fprintf(vita_stdout, "%s", lua_typename(L, type));
          break;
    }
  }
  fputc('\n', vita_stdout);
  return 0;
}

static const struct luaL_Reg printlib [] = {
  {"print", lj_cf_print_psp2},
  {NULL, NULL} /* end of array */
};

int luaopen_psp2print(lua_State *L)
{
  lua_getglobal(L, "_G");
  luaL_register(L, NULL, printlib);
  lua_pop(L, 1);
}