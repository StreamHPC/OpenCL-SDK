// OpenCL SDK includes
#include <CL/Utils/Utils.h>
#include <CL/SDK/Image.h>

// STL includes
#include <stdio.h>      // fprintf
#include <ctype.h>      // tolower

// stb includes
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

// OpenCL includes
#include <CL/cl.h>

UTILS_EXPORT
cl_sdk_image cl_sdk_read_image(const char* file_name, cl_int* err)
{
    cl_sdk_image im = { .width = 0, .height = 0, .pixel_size = 1, .pixels = NULL };
    im.pixels = stbi_load(file_name, &im.width, &im.height, &im.pixel_size, 0);

    if (im.width && im.height && im.pixel_size && im.pixels)
        *err = CL_SUCCESS;
    else {
        fprintf(stderr, "File read error!");
        *err = CL_INVALID_ARG_VALUE;
    }

    return im;
}

static char * to_lowercase(const char * s, char * d, size_t n)
{
    while(n > 0) {
        --n;
        d[n] = tolower(s[n]);
    }
    return d;
}

UTILS_EXPORT
void cl_sdk_write_image(const char * file_name, const cl_sdk_image * im, cl_int * err)
{
    *err = CL_SUCCESS;
    char fext[5] = {0, 0, 0, 0, 0};

#define IF_EXT(ext, func, err_text)                                                 \
    if (!strcmp(to_lowercase(file_name + strlen(file_name) - 4, fext, 4), ext)) {   \
        if (!func) {                                                                \
            fprintf(stderr, err_text);                                              \
            *err = CL_INVALID_ARG_VALUE;                                            \
        }                                                                           \
    }                                                                               \

    IF_EXT(".png", stbi_write_png(file_name, im->width, im->height, im->pixel_size, im->pixels, 0),
        "Not possible to write PNG file!")
    else IF_EXT(".bmp", stbi_write_bmp(file_name, im->width, im->height, im->pixel_size, im->pixels),
        "Not possible to write BMP file!")
    else IF_EXT(".jpg", stbi_write_jpg(file_name, im->width, im->height, im->pixel_size, im->pixels, 80),
        "Not possible to write JPG file!")
    else {
        fprintf(stderr, "Unknown file extension!");
        *err = CL_IMAGE_FORMAT_NOT_SUPPORTED;
    }

#undef IF_EXT
    return;
}
