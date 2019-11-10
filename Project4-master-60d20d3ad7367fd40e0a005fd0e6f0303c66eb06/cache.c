#include "cache.h"
#include "util.h"

/* cache.c : Implement your functions declared in cache.h */
cache_struct cache_line[2][4];
int miss_penalty;
uint32_t ***Cache;
int COUNT_LRU;

/***************************************************************/
/*                                                             */
/* Procedure: setupCache                  		       */
/*                                                             */
/* Purpose: Allocates memory for your cache                    */
/*                                                             */
/***************************************************************/

void setupCache(int capacity, int num_way, int block_size)
{
/*	code for initializing and setting up your cache	*/
/*	You may add additional code if you need to	*/
	//64 4 8
	int i,j; //counter
	int nset=0; // number of sets
	int _wpb=0; //words per block
	nset=capacity/(block_size*num_way); //2
	_wpb = block_size/BYTES_PER_WORD; //2

	Cache = (uint32_t  ***)malloc(nset*sizeof(uint32_t **));

	for (i=0;i<nset;i++) {
		Cache[i] = (uint32_t ** )malloc(num_way*sizeof(uint32_t*));
	}
	for (i=0; i<nset; i++){
		for (j=0; j<num_way; j++){
			Cache[i][j]=(uint32_t*)malloc(sizeof(uint32_t)*(_wpb));
		}
	}
	for(i=0;i<nset;i++){
		for(j=0;j<num_way;j++){
			cache_line[i][j].valid = 0;
			cache_line[i][j].dirty = 0;
			cache_line[i][j].count = 0;
			cache_line[i][j].tag = 0;
			cache_line[i][j].addr = 0;
		}
	}
	COUNT_LRU = 0;
}


/***************************************************************/
/*                                                             */
/* Procedure: setCacheMissPenalty                  	       */
/*                                                             */
/* Purpose: Sets how many cycles your pipline will stall       */
/*                                                             */
/***************************************************************/

void setCacheMissPenalty(int penalty_cycles)
{
/*	code for setting up miss penaly			*/
/*	You may add additional code if you need to	*/
	miss_penalty = penalty_cycles;

}

/* Please declare and implement additional functions for your cache */

/*read address from cache

	if hit, return that value from Cache[][][]
	if miss, put that block of data into Cache
			and put address into cache_line
			and also return smth to make 30 cycles stall

*/
int cache_read(uint32_t address){
	uint32_t b,s,value_b,value_s,value_tag,min;
	int chk_hit,E=4,k=-1,i;
	b = 1;
	s = 1;
	value_b = 0x4; // mask for offset
	value_s = 0x8; // same idea as value_b, for index
	value_tag = ~(~((uint32_t)(0))<<(32-s-b-2));//physical address 32 bits (m) = t+s+b so we find t

	value_b = (value_b&address)>>2; //get value from the address (CO)
	value_s = (value_s&address)>>3; // value of CI
	value_tag = value_tag&(address>>(b+s+2)); // value of CT

	chk_hit=0;
	//check two things: valid is 1 and tag is the same
	for(i=0;i<E;i++){
		if(cache_line[value_s][i].valid!=0){
			if(cache_line[value_s][i].tag==value_tag&&cache_line[value_s][i].valid==1){
				//HIT!!
				cache_line[value_s][i].count= COUNT_LRU;
				COUNT_LRU++;
				chk_hit=1;
				//printf("%d %d outttttttttttcacheeeeeeeeeeeeeeeeeeeee\n",Cache[value_s][i][value_b],value_b);
				return Cache[value_s][i][value_b];
			}
		}
	}
	//if it is not hit, so it is a miss.
	if(chk_hit==0){
		//MISS!!
		//check whether cache has more line to put new address or not if k is not -1 there is some space.
		for(i=0;i<E;i++){
			if(cache_line[value_s][i].valid==0){
				k=i;
				break;
			}
		}

		//has some more line to put new data in
		if(k!=-1){
			//if u can get inside here it means valid tag is still zero, so we dont need to
			//care about dirty bit here
			cache_line[value_s][k].valid=1;
			cache_line[value_s][k].tag=value_tag;
			cache_line[value_s][k].count=COUNT_LRU;
			cache_line[value_s][k].addr=address;
			COUNT_LRU++;

			//no way it will be dirty, it is empty line
			/*
			//if it is dirty, write value from cache to mem first then get write
			if(cache_line[value_s][k].dirty==1){
				mem_write_block(address,Cache[value_s][k]);
			}
			*/

			//same as 	Cache[value_s][k][0] = mem_read_32(address);
			//			Cache[value_s][k][1] = mem_read_32(address+4);
			//printf("HALO! %x\n",mem_read_32(address));
			mem_read_block(address,Cache[value_s][k]);
			//printf("%d %d Cache\n",Cache[value_s][k][0],Cache[value_s][k][1]);
			//not dirty anymore
			//cache_line[value_s][k].dirty = 0;
		}
		//no more line so evict some using LRU algorithm
		else{
			//EVICT!!
			//evict case
			min=0x7fffffff;
			//k for keeping the index to be evicted and put the new one
			for(i=0;i<E;i++){
				if(min>cache_line[value_s][i].count){
					min = cache_line[value_s][i].count;
					k=i;
				}
			}
			//if it is dirty, write value from cache to mem first
			if(cache_line[value_s][k].dirty==1){
				mem_write_block(cache_line[value_s][k].addr,Cache[value_s][k]);
			}
			//then put the new value in the place we evicted
			cache_line[value_s][k].valid = 1;
			cache_line[value_s][k].tag = value_tag;
			cache_line[value_s][k].count = COUNT_LRU;
			cache_line[value_s][k].addr=address;
			COUNT_LRU++;

			mem_read_block(address,Cache[value_s][k]);
			//printf("HALOHALO! %x\n",mem_read_32(address));
			//not dirty anymore
			cache_line[value_s][k].dirty = 0;
		}

	}
	return -1;
}
//use mem_write_block when deal with dirty bit, mem and cache. Not cache and user
int cache_write(uint32_t address,uint32_t value){
	//just do cache read to evict if the addr we want is not in the cache
	//we dont need value inside that cache. we just want to make dirty bit = 1

	//dirty bit is 1, so we have to write i back to mem
	uint32_t b,s,value_b,value_s,value_tag,min;
	int chk_hit,E=4,k=-1,i;
	b = 1;
	s = 1;
	value_b = 0x4; // mask for offset
	value_s = 0x8; // same idea as value_b, for index
	value_tag = ~(~((uint32_t)(0))<<(32-s-b-2));//physical address 32 bits (m) = t+s+b so we find t

	value_b = (value_b&address)>>2; //get value from the address (CO)
	value_s = (value_s&address)>>3; // value of CI
	value_tag = value_tag&(address>>(b+s+2)); // value of CT

	chk_hit=0;
	//check two things: valid is 1 and tag is the same
	for(i=0;i<E;i++){
		if(cache_line[value_s][i].valid!=0){
			if(cache_line[value_s][i].tag==value_tag&&cache_line[value_s][i].valid==1){
				//HIT!!
				cache_line[value_s][i].count= COUNT_LRU;
				COUNT_LRU++;
				chk_hit=1;
				//dirty bit, change the value in the cache
				cache_line[value_s][i].dirty = 1;
				Cache[value_s][i][value_b] = value;
				return 1;
				break;
			}
		}
	}
	//if it is not hit, so it is a miss.
	if(chk_hit==0){
		//MISS!!
		//check whether cache has more line to put new address or not if k is not -1 there is some space.
		for(i=0;i<E;i++){
			if(cache_line[value_s][i].valid==0){
				k=i;
				break;
			}
		}
		//k=cache_empty(cache_line[value_s],E);
		//has some more line to put new data in
		if(k!=-1){
			cache_line[value_s][k].valid=1;
			cache_line[value_s][k].tag=value_tag;
			cache_line[value_s][k].count=COUNT_LRU;
			cache_line[value_s][k].addr=address;
			COUNT_LRU++;
			//dont need to care about dirty bit
			/*if(cache_line[value_s][k].dirty==1){
				mem_write_block(address,Cache[value_s][k]);
			}*/
			//same as 	Cache[value_s][k][0] = mem_read_32(address);
			//			Cache[value_s][k][1] = mem_read_32(address+4);
			mem_read_block(address,Cache[value_s][k]);
			//printf("HALOWRITE! %x\n",mem_read_32(address));
			//dirty bit, change the value in the cache
			cache_line[value_s][k].dirty = 1;
			Cache[value_s][k][value_b] = value;
		}
		//no more line so evict some using LRU algorithm
		else{
			//EVICT!!
			//evict case
			min=0x7fffffff;
			//k for keeping the index to be evicted and put the new one
			for(i=0;i<E;i++){
				if(min>cache_line[value_s][i].count){
					min = cache_line[value_s][i].count;
					k=i;
				}
			}
			//if it is dirty, write value from cache to mem first
			if(cache_line[value_s][k].dirty==1){
				mem_write_block(cache_line[value_s][k].addr,Cache[value_s][k]);
			}
			//then put the new value in the place we evicted
			cache_line[value_s][k].valid = 1;
			cache_line[value_s][k].tag = value_tag;
			cache_line[value_s][k].count = COUNT_LRU;
			cache_line[value_s][k].addr=address;
			COUNT_LRU++;

			mem_read_block(address,Cache[value_s][k]);
			//printf("HALOWRITEWRITE! %x\n",mem_read_32(address));
			//dirty bit, change the value in the cache
			cache_line[value_s][k].dirty = 1;
			Cache[value_s][k][value_b] = value;
		}

	}
	return -1;
}

