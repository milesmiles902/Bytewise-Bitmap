#include "image.h"

#ifndef _FILE_H
#define _FILE_H

BMP *open(const char *filename);
int save(const BMP *image, const char *filename);
void destroy(BMP *image);
#endif
