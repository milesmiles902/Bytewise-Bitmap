#ifndef _IMAGE_H
#define _IMAGE_H
#include "header.h"

typedef struct{
  BMP_Header header;
  unsigned int data_size;
  unsigned int width;
  unsigned int height;
  unsigned int bytes_per_pixel;
  unsigned char *data; 
} BMP;
#endif
