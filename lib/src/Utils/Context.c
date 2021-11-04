// OpenCL SDK
#include <CL/Utils/Utils.h>
#include <CL/Utils/Error.h>
#include <CL/Utils/Context.h>

// STL includes
#include <stdlib.h> // malloc, free
#include <stdio.h>  // printf

static cl_uint MAXOCLPLAT = 65535;
static cl_uint MAXOCLDEV = 65535;

UTILS_EXPORT
cl_context cl_util_get_context(int plat_id, int dev_id, cl_device_type type, cl_int * error)
{
    cl_context result = NULL;
    cl_platform_id * platforms;
    cl_uint num_platforms = 0;
    cl_device_id * devices;
    cl_uint num_devices = 0;

    OCLERROR_RET(clGetPlatformIDs(MAXOCLPLAT, NULL, &num_platforms), *error, end);
    MEM_CHECK(platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * num_platforms), *error, end);
    OCLERROR_RET(clGetPlatformIDs(num_platforms, platforms, NULL), *error, plat);

    if (plat_id < 0 || plat_id >= num_platforms) {
        *error = CL_UTIL_INDEX_OUT_OF_RANGE; // "Invalid platform index provided for cl_util_get_context()"
        goto plat;
    }

    OCLERROR_RET(clGetDeviceIDs(platforms[plat_id], type, MAXOCLDEV, NULL, &num_devices), *error, plat);
    MEM_CHECK(devices = (cl_device_id *)malloc(sizeof(cl_device_id) * num_devices), *error, plat);
    OCLERROR_RET(clGetDeviceIDs(platforms[plat_id], type, num_devices, devices, NULL), *error, dev);

    if (dev_id < 0 || dev_id >= num_devices) {
        *error = CL_UTIL_INDEX_OUT_OF_RANGE; // "Invalid device index provided for cl_util_get_context()"
        goto dev;
    }

    OCLERROR_PAR(result = clCreateContext(NULL, 1, devices + dev_id, NULL, NULL, error), *error, dev);

dev:    free(devices);
plat:   free(platforms);
end:    return result;
}

UTILS_EXPORT
cl_device_id cl_util_get_device(int plat_id, int dev_id, cl_device_type type, cl_int * error)
{
    cl_device_id result = NULL;
    cl_platform_id * platforms;
    cl_uint num_platforms = 0;
    cl_device_id * devices;
    cl_uint num_devices = 0;

    OCLERROR_RET(clGetPlatformIDs(MAXOCLPLAT, NULL, &num_platforms), *error, end);
    MEM_CHECK(platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * num_platforms), *error, end);
    OCLERROR_RET(clGetPlatformIDs(num_platforms, platforms, NULL), *error, plat);

    if (plat_id < 0 || plat_id >= num_platforms) {
        *error = CL_UTIL_INDEX_OUT_OF_RANGE; // "Invalid platform index provided for cl_util_get_context()"
        goto plat;
    }

    OCLERROR_RET(clGetDeviceIDs(platforms[plat_id], type, MAXOCLDEV, NULL, &num_devices), *error, plat);
    MEM_CHECK(devices = (cl_device_id *)malloc(sizeof(cl_device_id) * num_devices), *error, plat);
    OCLERROR_RET(clGetDeviceIDs(platforms[plat_id], type, num_devices, devices, NULL), *error, dev);

    if (dev_id < 0 || dev_id >= num_devices) {
        *error = CL_UTIL_INDEX_OUT_OF_RANGE; // "Invalid device index provided for cl_util_get_context()"
        goto dev;
    }

    result = devices[dev_id];

dev:    free(devices);
plat:   free(platforms);
end:    return result;
}

// build program and show log if build is not successful
UTILS_EXPORT
cl_int cl_util_build_program(cl_program pr, const cl_device_id dev, const char * opt) {
    // if error
    cl_int err = clBuildProgram(pr, 1, &dev, opt, NULL, NULL);
    if (err != CL_SUCCESS) { // no error handling here as error from build program is more valuable
        char * program_log;
        size_t log_size = 0;
        clGetProgramBuildInfo(pr, dev, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        if ((program_log = (char *)malloc((log_size + 1) * sizeof(char)))) {
            clGetProgramBuildInfo(pr, dev, CL_PROGRAM_BUILD_LOG, log_size, program_log, NULL);
            program_log[log_size] = '\0';
            printf("Build log is:\n\n%s\n\n", program_log);
            free(program_log);
        }
    }
    return err;
}
