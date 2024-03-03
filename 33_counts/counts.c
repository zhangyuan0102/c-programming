#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
#include <assert.h>
counts_t * createCounts(void) {
  counts_t *array= malloc(sizeof(*array));
  array->array =NULL;
  array->size =0;
  return array;
}
one_count_t *creatCount(const char *name){
  one_count_t *array = malloc(sizeof(*array));
  if(name !=NULL){
    array->value =strdup(name);
    assert(strcmp(name,array->value)==0);
  }
  else{
    array->value =NULL;
  }
  array->num =1;
  return array;
}
void addCount(counts_t * c, const char * name) {
for(int i=0;i<c->size;i++){
  if(name ==NULL){
    if(c->array[i]->value ==NULL){
     c->array[i]->num++;
     return;
    }
  }else if(c->array[i]->value !=NULL &&strcmp(name,c->array[i]->value)==0){
    c->array[i]->num++;
    return;
  }
}
c->size++;
c->array =realloc(c->array,c->size*sizeof(*c->array));
c->array[c->size-1]=creatCount(name);
}
void printCounts(counts_t * c, FILE * outFile) {
    int unknownIndex = -1;
  for(int i=0; i < c->size; i++) {
    if(c->array[i]->value == NULL) {
      unknownIndex = i;
    } else {
      fprintf(outFile, "%s: %d\n", c->array[i]->value, c->array[i]->num);
    }
  }
  if (unknownIndex != -1) {
    fprintf(outFile, "<unknown> : %d\n", c->array[unknownIndex]->num);
  } 
}

void freeCounts(counts_t * c) {
   for(int i=0;i<c->size;i++){
  free(c->array[i]->value);
  free(c->array[i]);
  }
  free(c->array); 
  free(c);
}
