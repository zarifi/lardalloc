/*! \mainpage Lardalloc Memory Allocator
*  C Source File \n
*  Created 03/15/2008 06:32:43 PM\n
*  \n
*  By Lardmaster,\n
*  Anyone feel free to use it for any purposes\n
* \n
*  Uses unsigned shorts as pointers for the linked list of free block, to save memory.  Thus the max number of blocks is 65,534.\n
*  Simple fixed block sized memory allocator with free and allocate.
*/


#include "lardalloc.h"

/*!
*  Converts the LARD_PTR to a system wide pointer
*/
void * conv_to_ptr(const lardbuffer *b, LARD_PTR ptr) {
    return (char *)b + HEADER_SIZE + ptr*(b->size);
}
/*!
*  Converts a systemwide pointer to somewhere inside the buffer into an LARD_PTR which points locally
*/
LARD_PTR conv_to_short(const lardbuffer *b, const void * ptr) {
    return ((char *)ptr - (char *)b - HEADER_SIZE) / (b->size);
}

/*!
*  Allocates the buffer with a system malloc call.\n
*  \n
*  Elementsize is the block size for the allocator, and maxelements is the number of elements the allocator
*  Should pre-allocate for.
*/
lardbuffer * initialize_buffer(unsigned int elementsize, unsigned short maxelements) {
    int mallocsize = HEADER_SIZE + elementsize * MIN(maxelements,sizeof(LARD_PTR));
    lardbuffer * b = (lardbuffer *)(malloc(mallocsize));
    b->size = elementsize;
    b->first_free = 0;
    for (LARD_PTR i=0; i<maxelements-1; i++) {
        *(LARD_PTR *)conv_to_ptr(b,i) = i + 1;
    }
    *(LARD_PTR *)conv_to_ptr(b,maxelements-1) = USHRT_MAX;
    return (lardbuffer *)b;
}
/*!
* Returns a pointer to an allocated memory block of size b->size
*/
void * allocate(lardbuffer *b) {
    if (b->first_free == USHRT_MAX) {
        return NULL;
    }
    void * ptr = conv_to_ptr(b,b->first_free);
    b->first_free = *(LARD_PTR *)ptr;
    return ptr;
}

/*!
* Frees the memory block pointer to by ptr, which must be in larbuffer b
*/

void lardfree(lardbuffer *b, void * ptr) {
    LARD_PTR old_first = b->first_free;
    b->first_free = conv_to_short(b,ptr);
    *(LARD_PTR *) ptr = old_first;
}

