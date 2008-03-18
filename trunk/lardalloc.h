#ifndef LARDALLOC_H_INCLUDED
	#define LARDALLOC_H_INCLUDED
	
	#include <tigcclib.h>
	#include <limits.h>
	
	#define HEADER_SIZE sizeof(lardbuffer)
	#define LARD_PTR unsigned short
	#define MIN(a,b) (a<b?a:b)
	
	
	typedef struct lardbuffer {
			/*!
			*  Block size
			*/
  	  unsigned int size;
  	  /*!
  	  *  Lard_ptr to the first free memory block
  	  */
    	LARD_PTR first_free;
	} lardbuffer;
	
	lardbuffer * initialize_buffer(unsigned int elementsize, unsigned short maxelements);
	
	void * allocate(lardbuffer *b);
	
	void lardfree(lardbuffer *b, void * ptr);
#endif // LARDALLOC_H_INCLUDED




