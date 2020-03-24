#include "crypto_hash.h"

#define HASH_MASK(l) ((1<<(l))-1)

/* Assumes hash table size is a power of 2 <= 2^(sizeof(int)*8). */
/* hsize_bits gives the number of bits required to represent a   */
/* valid table index.                                            */
/* Output will be in the range 0..2^power - 1.              */
unsigned int hash_binary(unsigned char *input, 
	                       unsigned long length, 
	                       int power);

/* Assumes hash table size is prime p < 2^(sizeof(int)*8).       */
/* Output will be in the range 0..p - 1.                         */
unsigned int hash_prime(unsigned char *input, 
	                       unsigned long length, 
	                       unsigned int p);