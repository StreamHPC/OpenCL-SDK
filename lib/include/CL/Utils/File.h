#pragma once

// OpenCL Utils includes
#include "OpenCLUtils_Export.h"

// OpenCL includes
#include <CL/cl.h>

// read all the text file contents securely in ANSI C89
// return pointer to C-string with file contents
// can handle streams with no known size and no support for fseek
// based on https://stackoverflow.com/questions/14002954/ by Nominal Animal
UTILS_EXPORT
char * cl_util_read_text_file(const char * filename, size_t * length, cl_int * error);
