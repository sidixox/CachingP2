#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define OneKB 1024

// Define a structure for the cache
typedef struct Cache {
    int size; // Cache size in bytes
    int block_size; // Block size in bytes
    int associativity; // Associativity
    char policy[12]; // Replacement policy (RR or RND)
    int num_blocks; // num of blocks in the cache
    int index_bits;     // Number of index bits
    int tag_bits;       // Number of tag bits

    int physicalMemory; // To be stored as phyiscal memory,


} Cache;

// Initialize the cache
Cache* init_cache(int size, int block_size, int associativity, const char * policy, int physicalMemory) {
    Cache* cache = (Cache*)malloc(sizeof(Cache));
     //cacheSize=size,blockSize=blocksize
     //1 KB = 1024

    cache->size = size;
    cache->block_size = block_size;
    cache->associativity = associativity;
    strcpy(cache->policy, policy);
    cache->physicalMemory = physicalMemory;

    int cachesizeinKB = size * OneKB;
     int phyMeminKB = physicalMemory * OneKB;
    
    //num of blocks
    cache->num_blocks = (cachesizeinKB / phyMeminKB);
    return cache;
}

int main(int argc, char* argv[])
{
    char *traceFile = NULL;
    int cacheSizeKB = 0;
    int blockSize = 0;
    int associativity = 0;
    const char * replacementPolicy;
    int physicalMemory = 0;

    printf("When using -r flag, please enter Roundrobin or robin\n");
    printf("When using -s flag, please enter cacheSize in KB, if 512 KB, enter 512\n");
    printf("When using -b flag, please enter block size in Bytes, if 16 bytes, enter 16\n");
    printf(" ");
    
    for (int i = 1; i < argc; i++) {
        switch (argv[i][1]) {
            case 'f':
                if (i + 1 < argc) {
                    traceFile = argv[++i];
                } 
                break;
            case 's':
                if (i + 1 < argc) {
                    cacheSizeKB = atoi(argv[++i]);
                } 
                break;
            case 'b':
                if (i + 1 < argc) {
                    blockSize = atoi(argv[++i]);
                } 
                break;
            case 'a':
                if (i + 1 < argc) {
                    associativity = atoi(argv[++i]);
                } 
                break;
            case 'r':
                if (i + 1 < argc) {
                    replacementPolicy = argv[++i];
                } 
                break;
            case 'p':
                if (i + 1 < argc) {
                    physicalMemory = atoi(argv[++i]);
                } 
                break;
            default:
                fprintf(stderr, "Unknown option: %s\n", argv[i]);
                return 1; // Exit with an error code
        }
    }

    Cache* cache = init_cache(cacheSizeKB, blockSize, associativity, replacementPolicy, physicalMemory);

    // Validate and process the values as needed
    // (e.g., check if cache size is within range, handle different replacement policies, etc.)

    // Example: Printing the parsed values
    printf("Trace File: %s\n", traceFile);
    printf("Cache Size: %d KB\n", cache->size);
    printf("Block Size: %d bytes\n", cache->block_size);
    printf("Associativity: %d\n", cache->associativity);
    printf("Replacement Policy: %s\n", cache->policy);
    printf("Physical Memory: %d\n", cache->physicalMemory);
    printf("");
    printf("Number of Blocks: %d\n", cache->num_blocks);

    // Your program logic goes here
    // cache->size = size;
    // cache->block_size = block_size;
    // cache->associativity = associativity;
    // cache->policy = policy;
    //./mTwo.exe -f trace1.trc -s 512 -b 16 -a 2 -r RND -p 1GB

    return 0;
}
