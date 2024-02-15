#include "func.h"
#include <stdlib.h>

static int RGB2Gray(char red, char green, char blue){
  double gray = 0.2989*red + 0.5870*green+0.1140*blue;
  return (int) gray;
}

void edge(BMP *image, int threshold){
  int width = image->width;
  int height = image->height;
  char * * twoDGray = malloc(sizeof(char *) * height);
  int row;
  int col;
  for(row = 0; row<height; row++){
    twoDGray[row] = malloc(sizeof(char *) * width);
  }
  int pxl = 0;
  for(row = 0; row<height; row++){
    for(col = 0; col<width; col++){
      twoDGray[row][col] = RGB2Gray(image->data[pxl+2],
                                    image->data[pxl+1],
                                    image->data[pxl]);
      pxl+=3;
    }
  }
  pxl = 0;
  for(row=0; row<height; row++){
    pxl+=3;
    for(col=1;col<width;col++){
      int diff = twoDGray[row][col]-twoDGray[row][col-1];
      if(diff<0){
        diff = -diff;
      }
      if(diff>threshold){
        image->data[pxl+2] = 255;
        image->data[pxl+1] = 255;
        image->data[pxl] = 255;
      }
      else {
        image->data[pxl+2] = 0;
        image->data[pxl+1] = 0;
        image->data[pxl] = 0;
      }
      pxl += 3;
    }
  }
  for(row=0; row<height; row++){
    free(twoDGray[row]);
  }
  free(twoDGray);
}

