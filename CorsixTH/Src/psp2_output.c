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

static int lj_cf_print_psp2_generic(lua_State *L, FILE* vita_file)
{
  int i, type, size = 0, nargs = lua_gettop(L);
  const char* str = NULL;
  for (i = 0; i < nargs; i++) {
    if (i)
        fputc(' ', vita_file);
    type = lua_type(L, i);
    switch(type)
    {
        case LUA_TSTRING:  /* strings */
          str = lua_tostring(L, i);
          size = strlen(str);
          fwrite(str, 1, size, vita_file);
        case LUA_TBOOLEAN:  /* booleans */
          fprintf(vita_file, lua_toboolean(L, i) ? "true" : "false");
          break;
        case LUA_TNUMBER:  /* numbers */
          fprintf(vita_file, "%g", lua_tonumber(L, i));
          break;
        default:  /* other values */
          fprintf(vita_file, "%s", lua_typename(L, type));
          break;
    }
  }
  fputc('\n', vita_file);
  return 0;
}

/* Print replacement using stdout.txt */
int lj_cf_print_psp2(lua_State *L)
{
    return lj_cf_print_psp2_generic(L, vita_stdout);
}

/* Error replacement using stderr.txt */
int lj_cf_error_psp2(lua_State *L)
{
    return lj_cf_print_psp2_generic(L, vita_stderr);
}