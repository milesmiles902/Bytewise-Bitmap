#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bitmap/image.h"
#include "Bitmap/file.h"
#include "Bitmap/func.h"

#define _Threshold 10

int main(int argc, char **argv){
  if(argc < 4){
    return EXIT_FAILURE;
  }

  BMP *image = open(argv[1]);
  
  if(image == NULL){
    return EXIT_FAILURE;
  }
 
  if(strcmp(argv[2],"edge") == 0){
    edge(image, _Threshold);
  }
  
  if(save(image, argv[3]) == 0){
    destroy(image);
    return EXIT_FAILURE;
  }

  destroy(image);
  return EXIT_SUCCESS;
}
