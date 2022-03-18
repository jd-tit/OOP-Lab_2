//
// Created by jdt on 2022-03-05.
//

#ifndef LAB2_VECTOR_BASE_H
#define LAB2_VECTOR_BASE_H

#define INITIAL_MAX_SIZE 15
#define EXTEND_FACTOR 2

enum DataTypes{TRANSACTION, SIZE_T};

#include <stdio.h>

typedef struct Vector {
    size_t max_len, crt_len, element_size;
    void* contents;
} Vector;

/**
 * Create a Vector
 * @param type - currently ignored, as only Transaction vectors were necessary
 * @return A pointer to the new vector object
 */
Vector* make_vector(char type);

/**
 * Deallocate a vector
 * @param old_vector - the vector to be deallocated
 */
void destroy_vector(Vector* old_vector);

/**
 * Add an element ot the vector
 * @param vector - the vector to add to
 * @param element - a pointer to the element to be added
 * @return The exit code, either EXIT_SUCCESS or EXIT_FAILURE
 */
int push_back(Vector* vector, void* element);

/**
 * Increase the length of a vector by a fixed factor
 * @param vector - the vector to be adjusted
 * @return The exit code, either EXIT_SUCCESS or EXIT_FAILURE.
 */
int extend(Vector* vector);

/**
 * Copy a vector and its contents.
 * @param v - the vector to be copied
 * @return A pointer to the new Vector, or NULL if the copy failed.
 */
Vector* copy_vector(Vector* v);

#endif //LAB2_VECTOR_BASE_H
