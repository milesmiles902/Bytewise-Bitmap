#include <stdio.h>
#include <stdlib.h>
#include "file.h"

#define MAGIC_VALUE 0x4D42
#define BITS_PER_PIXEL 24
#define NUM_PLANE 1
#define COMPRESSION 0
#define BITS_PER_BYTE 8

static int checkHeader(BMP_Header *header){
  if((header->type)!= MAGIC_VALUE){
    return 0;
  }
  if((header->bits) != BITS_PER_PIXEL){
    return 0;
  }
  if((header->planes) != NUM_PLANE){
    return 0;
  }
  if((header->compression) != COMPRESSION){
    return 0;
  }
  return 1;
}

BMP *cleanUp(FILE *fptr, BMP *image){
  if(fptr != NULL){
    fclose(fptr);
  }
  if(image != NULL){
    if(image->data != NULL){
      free(image->data);
    }
    free(image);
  }
  return NULL;
}

BMP *open(const char *filename){
  FILE *fptr = NULL;
  BMP *image = NULL;
  fptr = fopen(filename, "r");
  if(fptr == NULL){
    return cleanUp(fptr, image);
  }
  image = malloc(sizeof(BMP));
  if(fread(&(image->header),sizeof(BMP_Header), 1, fptr) != 1){
    return cleanUp(fptr, image);
  }
  if(checkHeader(&(image->header)) == 0){
    return cleanUp(fptr, image);
  }
  image->data_size = (image->header).size - sizeof(BMP_Header);
  image->width =  (image->header).width;
  image->height = (image->header).height;
  image->bytes_per_pixel = (image->header).bits/BITS_PER_BYTE;
  image->data = malloc(sizeof(unsigned char) *(image->data_size));
  if((image->data) == NULL){
    return cleanUp(fptr, image);
  }
  if(fread(image->data, sizeof(char),image->data_size, fptr) != (image->data_size)){
    return cleanUp(fptr, image);
  }
  char onebyte;
  if(fread(&onebyte, sizeof(char), 1, fptr)!=0){
    return cleanUp(fptr, image);
  }
  fclose(fptr);
  return image;
}

int save(const BMP *image, const char *filename){
  FILE *fptr = NULL;
  fptr = fopen(filename, "w");
  if(fptr == NULL){
    return 0;
  }
  if(fwrite(&(image->header), sizeof(BMP_Header), 1, fptr) != 1){
    fclose(fptr);
    return 0;
  }
  if(fwrite(image->data, sizeof(char), image->data_size, fptr) != (image->data_size)){
    fclose(fptr);
    return 0;
  }
  fclose(fptr);
  return 1;
}

void destroy(BMP *image){
  free(image->data);
  free(image);
};

