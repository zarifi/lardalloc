#ifndef LARDALLOC_H_INCLUDED
#define LARDALLOC_H_INCLUDED
#include <tigcclib.h>
#include <limits.h>
#define HEADER_SIZE sizeof(lardbuffer)
#define LARD_PTR unsigned short
#define MIN(a,b) a<b?a:b


/*
*  block size, and the short pointer to the first free block
*/

typedef struct lardbuffer {
    unsigned int size;
    unsigned short first_free;
} lardbuffer;

lardbuffer * initialize_buffer(unsigned int elementsize, unsigned short maxelements);
void * allocate(lardbuffer *b);
void lardfree(lardbuffer *b, void * ptr);
LARD_PTR deref(lardbuffer *b, LARD_PTR ptr);
#endif // LARDALLOC_H_INCLUDED


