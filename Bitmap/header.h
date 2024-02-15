#include <stdint.h>

#ifndef _HEADER_H
#define _HEADER_H
#pragma pack(1)

typedef struct{
  uint16_t type;
  uint32_t size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset;
  uint32_t header_size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bits;
  uint32_t compression;
  uint32_t imagesize;
  uint32_t xresolution;
  uint32_t yresolution;
  uint32_t ncolors;
  uint32_t importantcolors;
} BMP_Header;
#endif

