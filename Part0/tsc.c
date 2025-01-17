/**
 * @file tsc.c
 * @brief Implementation of TSC performance measurement functions.
 */

#include "tsc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief Number of iterations for performance evaluation.
 */
#define SIZE 100000

unsigned long long start_timer() {
    unsigned int hi = 0, lo = 0;
    asm volatile("cpuid\n\trdtscp\n\tmov %%edx, %0\n\tmov %%eax, %1\n"
                 : "=r" (hi), "=r" (lo)
                 :: RDTSC_DIRTY);
    return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

unsigned long long stop_timer() {
    unsigned int hi = 0, lo = 0;
    asm volatile("rdtscp\n\tmov %%edx, %0\n\tmov %%eax, %1\n\tcpuid\n"
                 : "=r" (hi), "=r" (lo)
                 :: RDTSC_DIRTY);
    return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

double dtime(long long start, long long end) {
    return (double)(end - start - TSCCYCLES);
}

int cmp(const void *x, const void *y) {
    double xx = *(double *)x, yy = *(double *)y;
    return (xx < yy) ? -1 : (xx > yy);
}

double tmean(double ar[], int n) {
    qsort(ar, n, sizeof(double), cmp);
    double q1 = ar[n / 4], q2 = ar[n / 2], q3 = ar[3 * n / 4];
    double sum = 0.0, k = 1.0;
    int i = 0;
    while (ar[i++] < q2 - k * (q3 - q1));
    int j = i;
    while (ar[j] < q2 + k * (q3 - q1) && j < n) {
        sum += ar[j++];
    }
    return sum / (double)(j - i);
}

void eval_tsc_cycles() {
    double tsum = 0.0, t2sum = 0.0, tmin = 1e30, tmax = 0.0;
    double tresults[SIZE];

    for (int i = 0; i < SIZE; i++) {
        long long start = start_timer();
        long long end = stop_timer();
        double t = dtime(start, end);
        tresults[i] = t;
        tsum += t;
        t2sum += t * t;
        if (t < tmin) tmin = t;
        if (t > tmax) tmax = t;
    }

    double avg = tsum / SIZE;
    double var = sqrt((t2sum + avg * avg * SIZE - 2 * avg * tsum) / SIZE);
    double ttavg = tmean(tresults, SIZE);

    printf("Average: %f\tMin: %f\tMax: %f\tVariance: %f\tTrimmed Avg: %f\n", avg, tmin, tmax, var, ttavg);
}
