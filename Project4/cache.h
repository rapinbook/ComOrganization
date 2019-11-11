#ifndef _CACHE_H_
#define _CACHE_H_

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* cache.h : Declare functions and data necessary for your project*/

extern int miss_penalty; // number of cycles to stall when a cache miss occurs
extern uint32_t ***Cache; // data cache storing data [set][way][byte]
//here for storing line of each set of the cache not data
extern int COUNT_LRU;
typedef struct{
	int valid;
	int dirty;
	//count is for LRU
	/*
		all cache lines will have different value of count. The cache with the
		lowest value of count is the one to be evicted because it is least recently used.

		update count every time it is hit or added in to the set
	*/
	int count;
	uint32_t addr;
	unsigned long long tag; //hex value of tag
}cache_struct; //cache[S][E]
extern cache_struct cache_line[2][4];
void setupCache(int, int, int);
void setCacheMissPenalty(int);
int cache_read(uint32_t address);
int cache_write(uint32_t address,uint32_t value);

#endif

