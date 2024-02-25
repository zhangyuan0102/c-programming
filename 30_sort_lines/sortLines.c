#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void printData(char ** data,size_t count){
  for(int i=0;i<count;i++){
    printf("%s",data[i]);
    free(data[i]);
  }
}
void getData(FILE *f){
  char ** array =NULL;
  char * line = NULL;
  size_t sz =0;
  size_t i=0;
  while(getline(&line,&sz,f)>=0){
    array = realloc(array,sz*sizeof(*array)+sizeof(*array));
    array[i] = line;
    line = NULL;
    i++;
  }
  free(line);
  sortData(array,i);
  printData(array,i);
  free(array);
}

int main(int argc, char ** argv) {
  if(argc ==1){
    getData(stdin);
  }
  if(argc >1){
    for(int i=1;i<argc;i++){
            FILE * f = fopen(argv[i], "r");
      if (f==NULL) {
	fprintf(stderr, "File not found\n");
	return EXIT_FAILURE;
      }
       getData(f);
    if (fclose(f)!=0) {
      fprintf(stderr, "File could not close properly\n");
      return EXIT_FAILURE;
    }
  }
  }
    return EXIT_SUCCESS;
}
