#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  char * outputName = malloc(strlen(inputName) + 12);
   strcpy(outputName, inputName);
  strcat(outputName, ".counts");
  return outputName;
}

