#ifndef VECTOR_H_
#define VECTOR_H_

#include <sys/types.h>

typedef struct vector_t vector_t;

vector_t* vector_new();
void vector_delete(vector_t* v);
void vector_set(vector_t* v, size_t loc, int value);
int vector_get(vector_t* v, size_t loc);

#endif