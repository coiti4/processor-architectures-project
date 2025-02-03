/*!
 * \file cache_tlb_sim.h
 * \brief Header for cache and TLB simulation routines.
 *
 * This file contains global variables and function prototypes
 * for simulating a data cache (with a given associativity, line size,
 * etc.) and a TLB (with a given number of entries, associativity, page size).
 */

#ifndef CACHE_TLB_SIM_H
#define CACHE_TLB_SIM_H

#include <assert.h>
#include <stdio.h>

/* ----------------------------------------------------------------
   Data Cache Definitions
   ---------------------------------------------------------------- */

/*! \brief Maximum associativity for data cache. */
#define mway    4

/*! \brief Maximum number of sets for data cache. */
#define mnsets  1024

/* ----------------------------------------------------------------
   TLB Definitions
   ---------------------------------------------------------------- */

/*! \brief Maximum associativity for TLB. */
#define mtway   4

/*! \brief Maximum number of sets for TLB. */
#define mtnsets 32

/*!
 * \brief Page size in bytes for TLB simulation.
 *        Used to divide addresses into pageNumber + offset.
 */
#define pagesize 1024

/*!
 * \brief Global counter that increments on each memory access.
 */
extern int am;

/*!
 * \brief Global counter for data cache misses.
 */
extern int dc;

/*!
 * \brief Global counter for TLB misses.
 */
extern int dtlb;

/*!
 * \brief Data cache tag store.
 *        ETIQ[index][set] = tag.
 */
extern int ETIQ[mnsets][mway];

/*!
 * \brief Data cache LRU store.
 *        LRU[index][set] = recency timestamp.
 */
extern int LRU[mnsets][mway];

/*!
 * \brief TLB tag store.
 *        tETIQ[index][set] = TLB tag.
 */
extern int tETIQ[mtnsets][mtway];

/*!
 * \brief TLB LRU store.
 *        tLRU[index][set] = recency timestamp.
 */
extern int tLRU[mtnsets][mtway];

/*!
 * \brief Line size (bytes) for data cache lines.
 */
extern int line;

/*!
 * \brief Total data cache size (bytes).
 */
extern int size;

/*!
 * \brief Associativity for the data cache.
 */
extern int way;

/*!
 * \brief Number of sets for the data cache: nsets = size/(way*line).
 */
extern int nsets;

/*!
 * \brief Total number of TLB entries.
 */
extern int tsize;

/*!
 * \brief Associativity of the TLB.
 */
extern int tway;

/*!
 * \brief Number of sets in the TLB: tsets = tsize/tway.
 */
extern int tsets;

/* ----------------------------------------------------------------
   Function Prototypes
   ---------------------------------------------------------------- */

/*!
 * \brief Initialize data cache with current 'size', 'line', and 'way' global variables.
 */
void initcache();

/*!
 * \brief Access the data cache with address \p addr.
 * \param addr The memory address being accessed.
 * \return 1 if miss, 0 if hit.
 */
int cache_access(unsigned long addr);

/*!
 * \brief Initialize TLB with current 'tsize' and 'tway'.
 */
void inittlb();

/*!
 * \brief Access the TLB with address \p addr.
 * \param addr The memory address being translated.
 * \return 1 if TLB miss, 0 if TLB hit.
 */
int tlb_access(unsigned long addr);

/*!
 * \brief Perform one combined memory access at address \p z:
 *        increments the global 'am', checks TLB, then checks data cache.
 * \param z The memory address accessed.
 */
void ac(unsigned long z);

#endif
