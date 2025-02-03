/*!
 * \file simulate_cache.c
 * \brief Example driver for data cache and TLB simulations.
 *
 * This file shows how to configure and initialize
 * the data cache and TLB, then perform random memory
 * accesses to measure misses.
 */

#include <stdio.h>
#include <stdlib.h>
#include "cache_tlb_sim.h"

int main(void)
{
    /* Configure the data cache. */
    size = 4096;     /* 4 KB total cache size */
    line = 16;       /* line size in bytes */
    way  = 1;        /* direct-mapped cache */
    initcache();     /* init with above parameters */

    /* Configure the TLB. */
    tsize = 8;       /* 8 total TLB entries */
    tway  = 1;       /* direct-mapped TLB */
    inittlb();       /* init TLB */

    /* Let's do 200 random accesses. */
    for(int i=0; i<200; i++){
        unsigned long addr = rand() % 65536; /* random 16-bit address */
        ac(addr);
    }

    printf("Accesses:      %d\n", am);
    printf("Cache misses:  %d\n", dc);
    printf("TLB misses:    %d\n", dtlb);

    return 0;
}
