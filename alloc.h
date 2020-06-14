#ifndef ALLOC_H
#define ALLOC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * Machine word size. Depending on the architecture,
 * can be 4 or 8 bytes.
 */
typedef intptr_t word_t;

/**
 * Allocated block of memory. Contains the object header structure,
 * and the actual payload pointer.
 */
struct Block {

    // -------------------------------------
    // 1. Object header
    size_t size; /* Block size */
    bool   used; /* Whether this block is currently used */
    struct Block *next; /* Next block on the list */

    // -------------------------------------
    // 2. User data
    word_t data[1];
};

/**
 * @brief Allocates a block of memory of (at least) 'size' bytes.
 */
word_t* alloc(size_t size);

/**
 * @brief Returns the object header.
 */
struct Block* getHeader(word_t *data);

#endif