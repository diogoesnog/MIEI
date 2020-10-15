#include "hash_function.h"

unsigned int hash_power2(unsigned char *input, 
	          unsigned long length, int power) {
	static unsigned char scratch[32];
	unsigned int hash_val;
	crypto_hash(scratch,input,length);
	hash_val = *((unsigned int*)scratch) & HASH_MASK(power);
	return hash_val;
}

unsigned int hash_prime(unsigned char *input, 
	       unsigned long length, unsigned int p) {
	static unsigned char scratch[32];
	unsigned int hash_val;
	crypto_hash(scratch,input,length);
	hash_val = *((unsigned int*)scratch) % p;
	return hash_val;
}
