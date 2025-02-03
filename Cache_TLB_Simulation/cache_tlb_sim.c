/*!
 * \file cache_tlb_sim.c
 * \brief Implementation of cache and TLB simulation routines.
 *
 * Provides functions to initialize and access both a data cache
 * and a TLB, tracking miss counts and recency (LRU).
 */

#include "cache_tlb_sim.h"

/* ----------------------------------------------------------------
   Global variables declared in cache_tlb_sim.h
   ---------------------------------------------------------------- */
int am   = 0;
int dc   = 0;
int dtlb = 0;

int ETIQ[mnsets][mway];
int LRU[mnsets][mway];

int tETIQ[mtnsets][mtway];
int tLRU[mtnsets][mtway];

int line;
int size;
int way;
int nsets;

int tsize;
int tway;
int tsets;

/* ----------------------------------------------------------------
   Internal helpers (static)
   ---------------------------------------------------------------- */

/*!
 * \brief Find the line to evict in data cache set \p index using LRU.
 * \param index The set index in the data cache.
 * \return The line number to evict (0..way-1).
 */
static inline int find_evict_line(int index) {
    int oldest = 0;
    int minLRU = LRU[index][0];
    for (int j = 1; j < way; j++){
        if (LRU[index][j] < minLRU){
            minLRU = LRU[index][j];
            oldest = j;
        }
    }
    return oldest;
}

/*!
 * \brief Find the TLB entry to evict for set \p index using LRU.
 * \param index The TLB set index.
 * \return The entry number to evict (0..tway-1).
 */
static inline int find_evict_tlb(int index) {
    int oldest = 0;
    int minVal = tLRU[index][0];
    for (int j = 1; j < tway; j++){
        if (tLRU[index][j] < minVal){
            minVal = tLRU[index][j];
            oldest = j;
        }
    }
    return oldest;
}

/* ----------------------------------------------------------------
   Data Cache Routines
   ---------------------------------------------------------------- */

void initcache() {
    nsets = size / (way * line);

    am = 0;     /* reset access counter */
    dc = 0;     /* reset data cache misses */
    for (int j = 0; j < nsets; j++) {
        for (int k = 0; k < way; k++){
            LRU[j][k]  = 0;
            ETIQ[j][k] = -1;
        }
    }
}

int cache_access(unsigned long addr) {
    unsigned long lineAddr = addr / line;
    int tag   = lineAddr / nsets;
    int index = lineAddr % nsets;

    /* check for hit */
    for (int set = 0; set < way; set++){
        if (ETIQ[index][set] == tag) {
            LRU[index][set] = am;
            return 0; /* hit */
        }
    }
    /* miss => evict */
    int j = find_evict_line(index);
    ETIQ[index][j] = tag;
    LRU[index][j]  = am;
    return 1; /* miss */
}

/* ----------------------------------------------------------------
   TLB Routines
   ---------------------------------------------------------------- */

void inittlb() {
    tsets = tsize / tway;

    dtlb = 0;
    for (int j = 0; j < tsets; j++){
        for (int k = 0; k < tway; k++){
            tLRU[j][k]  = 0;
            tETIQ[j][k] = -1;
        }
    }
}

int tlb_access(unsigned long addr) {
    /* Page-based address => separate into pageNumber + offset */
    unsigned long pageNumber = addr / pagesize;
    int index = pageNumber % tsets;
    int tag   = pageNumber / tsets;

    /* search set for tag */
    for (int i = 0; i < tway; i++) {
        if (tETIQ[index][i] == tag) {
            tLRU[index][i] = am;
            return 0; /* TLB hit */
        }
    }
    /* miss => evict */
    int victim = find_evict_tlb(index);
    tETIQ[index][victim] = tag;
    tLRU[index][victim]  = am;
    return 1; /* TLB miss */
}

/* ----------------------------------------------------------------
   Combined Access
   ---------------------------------------------------------------- */

void ac(unsigned long z) {
    /* increment global 'am' for each memory access */
    am++;

    /* TLB check */
    if (tlb_access(z))
        dtlb++;

    /* data cache check */
    if (cache_access(z))
        dc++;
}
