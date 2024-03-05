#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open file for reading\n");
    return NULL;
  } 
  counts_t *c = createCounts();
  char *line = NULL;
  size_t sz = 0;
  char *value=NULL;
  while(getline(&line,&sz,f)>=0){
    char *n =strchr(line,'\n');
    if(n !=NULL){
      *n ='\0';
    }
 
  value =lookupValue(kvPairs,line);
  addCount(c,value);
  }
  free(line);
  fclose(f);
  return c;
}

int main(int argc, char ** argv) {
      if (argc < 3) {
    fprintf(stderr,"No inputFile\n");
    return EXIT_FAILURE;
  }

    kvarray_t *kv=readKVs(argv[1]);

    for(int i=2;i<argc;i++){
    counts_t *c = countFile(argv[i],kv);
    char * outName = computeOutputFileName(argv[i]);
    FILE *f = fopen(outName, "w");
    printCounts(c,f);
    fclose(f);
    free(outName);
    freeCounts(c);
    }
    freeKVs(kv);

  return EXIT_SUCCESS;
}
