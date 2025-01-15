/**
 * @file tsc.h
 * @brief Header for Time Stamp Counter (TSC) performance measurement.
 */

#ifndef TSC_H
#define TSC_H

#include <x86intrin.h>

/**
 * @brief Define adjustment for RDTSC measurement overhead.
 */
#define TSCCYCLES 13.0

/**
 * @brief Number of iterations for performance evaluation.
 */
#define N 100000

#ifdef __i386__
    #define RDTSC_DIRTY "%eax", "%ebx", "%ecx", "%edx"
#elif __x86_64__
    #define RDTSC_DIRTY "%rax", "%rbx", "%rcx", "%rdx"
#else
    #error Unknown platform
#endif

/**
 * @brief Starts the timer using the TSC register.
 * @return The current TSC value.
 */
unsigned long long start_timer();

/**
 * @brief Stops the timer using the TSC register.
 * @return The current TSC value.
 */
unsigned long long stop_timer();

/**
 * @brief Computes the elapsed time between two TSC values.
 * @param start The start TSC value.
 * @param end The end TSC value.
 * @return The elapsed time in cycles.
 */
double dtime(long long start, long long end);

/**
 * @brief Evaluates the overhead of TSC measurement.
 */
void eval_tsc_cycles();

#endif // TSC_H
