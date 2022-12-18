#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct vector_t {
    size_t size;
    int* data;
};

/**
 * Utility function to handle allocation failures.
 * In this case we print a message and exit.
 */  
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/**
 * Bad example of how to create a new vector 
 */
vector_t* bad_vector_new() {
    // Create the vector and a pointer to it
    vector_t* retval, v;
    retval = &v;

    // Initialize attributes
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval;
}

/**
 * Another suboptimal way of creating a vector
 */
vector_t also_bad_vector_new() {
    // Create the vector
    vector_t v;

    // Initialize attributes
    v.size = 1;
    v.data = malloc(sizeof(int));
    if (v.data == NULL) {
        allocation_failed();
    }
    v.data[0] = 0;
    return v;
}

/**
 * Create a new vector with a size (length) of 1
 * and set its single component to zero
 */
vector_t* vector_new() {
    vector_t* retval = (vector_t*) malloc(sizeof(vector_t));;

    if (retval == NULL) {
        allocation_failed();
    }

    retval->size = 10;
    retval->data = (int*) malloc(sizeof(int) * retval->size);

    if (retval->data == NULL) {
        free(retval);
        allocation_failed();
    }

    for (size_t i = 0; i < retval->size; i++) {
        retval->data[i] = 0;
    }

    return retval;
}

/**
 * Return the value at the specified location/component "loc" of the vector
 */
int vector_get(vector_t* v, size_t loc) {
    if (v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    if (loc < v->size) {
        return v->data[loc];
    } else {
        return 0;
    }
}

/**
 * Free up the memory allocated for the passed vector.
 * Remember, you need to free up ALL the memory that was allocated.
 */
void vector_delete(vector_t* v) {
    if (v == NULL) {
        fprintf(stderr, "vector_delete: passed a NULL vector.\n");
        abort();
    }

    free(v->data);
    free(v);
}

/**
 * Set a value in the vector. If the extra memory allocation fails, call
 * allocation_failed().
 */
void vector_set(vector_t* v, size_t loc, int value) {
    if (v == NULL) {
        fprintf(stderr, "vector_set: passed a NULL vector.\n");
        abort();
    }

    if (loc >= v->size) {
        int* new_data = (int*) calloc(loc + 1, sizeof(int));
        if (new_data == NULL) {
            allocation_failed();
        }

        for (size_t i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }

        free(v->data);
        v->size = loc + 1;
        v->data = new_data;
    }

    v->data[loc] = value;
}