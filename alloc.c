#include "alloc.h"
#include <unistd.h>

/**
 * Heap start. Initialised on first allocation.
 */
static struct Block *heapStart = NULL;

/**
 * Current top. Updated on each allocation.
 */
static struct Block *top = NULL;


/**
 * Aligns the size by the machine word.
 */
static inline size_t align(size_t n) {
  return (n + sizeof(word_t) - 1) & ~(sizeof(word_t) - 1);
}

/**
 * Returns total allocation size, reserving in addition the space for
 * the Block structure (object header + first data word).
 *
 * Since the `word_t data[1]` already allocates one word inside the Block
 * structure, we decrease it from the size request: if a user allocates
 * only one word, it's fully in the Block struct.
 */
static inline size_t allocSize(size_t size) {
  return size + sizeof(struct Block) - sizeof(word_t);
}

static struct Block* requestFromOS(size_t size)
{
    /* Current head break */
    struct Block *block = (struct Block*) sbrk(0);

    /* Out of memory (OOM) */
    if(sbrk(allocSize(size)) == (void *) -1) {
        return NULL;
    }
    return block;
}


/**
 * @brief Allocates a block of memory of (at least) 'size' bytes.
 */
word_t* alloc(size_t size)
{
    size = align(size);

    struct Block *block = requestFromOS(size);

    block->size = size;
    block->used = true;

    // Init heap.
    if(heapStart == NULL) {
        heapStart = block;
    }

    // Chain the blocks.
    if(top != NULL) {
        top->next = block;
    }

    top = block;

    // User payload:
    return block->data;
}

/**
 * @brief Returns the object header.
 */
struct Block* getHeader(word_t *data)
{
    return (struct Block*)((char *) data + sizeof(word_t) - sizeof(struct Block));
}