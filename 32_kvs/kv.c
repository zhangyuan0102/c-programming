#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    kvarray_t *kv_array = malloc(sizeof(kvarray_t));
    if (kv_array == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }
    kv_array->pair_array = NULL;
    kv_array->size = 0;

    char *line = NULL;
    size_t sz = 0;

    while (getline(&line, &sz, file) != -1) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        char *equal_sign_pos = strchr(line, '=');
        if (equal_sign_pos == NULL) {
            fprintf(stderr, "Invalid input: No '=' found\n");
            continue;
        }

        char *key = malloc(equal_sign_pos - line + 1);
        char *value = strdup(equal_sign_pos + 1); 

        if (key == NULL || value == NULL) {
            perror("Memory allocation error");
            fclose(file);
            free(line);
            free(key);
            free(value);
            free(kv_array->pair_array);
            free(kv_array);
            return NULL;
        }

        strncpy(key, line, equal_sign_pos - line);
        key[equal_sign_pos - line] = '\0';

        kv_array->pair_array = realloc(kv_array->pair_array, (kv_array->size + 1) * sizeof(kvpair_t));
        if (kv_array->pair_array == NULL) {
            perror("Memory allocation error");
            fclose(file);
            free(line);
            free(key);
            free(value);
            free(kv_array);
            return NULL;
        }

        kv_array->pair_array[kv_array->size].key = key;
        kv_array->pair_array[kv_array->size].value = value;
        kv_array->size++;
    }

    free(line);
    fclose(file);

    return kv_array; 
}

void freeKVs(kvarray_t * pairs) {
    if (pairs == NULL) {
        return;
    }

    for (size_t i = 0; i < pairs->size; i++) {
        free(pairs->pair_array[i].key);
        free(pairs->pair_array[i].value);
    }

    free(pairs->pair_array);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
    if (pairs == NULL || pairs->pair_array == NULL) {
        printf("No key/value pairs to print.\n");
        return;
    }

    for (size_t i = 0; i < pairs->size; i++) {
        printf("key = '%s' value = '%s'\n", pairs->pair_array[i].key, pairs->pair_array[i].value);
    }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    if (pairs == NULL || pairs->pair_array == NULL || key == NULL) {
        return NULL; 
    }

    for (size_t i = 0; i < pairs->size; i++) {
        if (strcmp(pairs->pair_array[i].key, key) == 0) {
            return pairs->pair_array[i].value; 
        }
    }
    return NULL;
}
