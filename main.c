#include "alloc.h"
#include "assert.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // --------------------------------------
    // Test case 1: Alignment
    //
    // A request for 3 bytes is aligned to 8.
    //
    word_t *p1 = alloc(3);
    struct Block *p1b = getHeader(p1);
    assert(p1b->size == sizeof(word_t));

    // --------------------------------------
    // Test case 2: Exact amount of aligned bytes
    //
    word_t *p2 = alloc(8);
    struct Block *p2b = getHeader(p2);
    assert(p2b->size == 8);

    printf("\nAll assertions passed!\n");
    return 0;
}