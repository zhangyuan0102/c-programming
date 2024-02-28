#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * readKV(FILE *f) {
  char *line = NULL;
  size_t sz = 0;
  if (f == NULL) {
    return NULL;
  }

  if (getline(&line, &sz, f) <= 0) {
    free(line);
    return NULL;
  }

  char * p = strchr(line, '=');
  if (p == NULL) {
    fprintf(stderr, "Not a key=value pair: %s", line);
    return NULL;
  }

  kvpair_t * answer = malloc(sizeof(*answer));
  *p = '\0';
  answer->key = line;
  p++;
  char * end = strchr(p, '\n');
  if (end != NULL) {
    *end = '\0';
  }
  answer->value = p;
  return answer;
}


kvarray_t * readKVs(const char * fname) {
  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file for reading\n");
    return NULL;
  }
  kvarray_t * answer = malloc(sizeof(*answer));
  answer->numPairs = 0;
  answer->pairs = NULL;
  kvpair_t * pair = NULL;
  while((pair = readKV(f)) != NULL) {
    answer->numPairs++;
    answer->pairs = realloc(answer->pairs,
			    answer->numPairs
			    * sizeof(*answer->pairs));
    answer->pairs[answer->numPairs - 1] = pair;
  }
  fclose(f);
  return answer;
}


void freeKVs(kvarray_t * pairs) {
  for(int i=0; i < pairs->numPairs; i++) {
    free(pairs->pairs[i]->key); 
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for(int i=0; i < pairs->numPairs; i++) {
    printf("key = '%s' value = '%s'\n",
	   pairs->pairs[i]->key,
	   pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i=0; i < pairs->numPairs; i++) {
    if (strcmp(pairs->pairs[i]->key,key) == 0) {
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}

