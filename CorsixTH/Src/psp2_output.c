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
