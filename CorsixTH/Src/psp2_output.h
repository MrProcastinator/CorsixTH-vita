#ifndef VITA_OUTPUT_H_
#define VITA_OUTPUT_H_

#undef stdout
#define stdout vita_stdout

#undef stderr
#define stderr vita_stderr

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

extern FILE* vita_stdout;
extern FILE* vita_stderr;

void load_output_files(FILE** out, FILE** err);

#ifdef __cplusplus
}
#endif

#endif