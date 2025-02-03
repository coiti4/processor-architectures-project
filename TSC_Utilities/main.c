/**
 * @file main.c
 * @brief Main program to evaluate TSC performance.
 * @details Compile with 'gcc -O3 -o tsc_test.elf main.c tsc.c -lm'.
 * Run with 'taskset -c N ./tsc_test.elf' with N being the core number.
 * The program will output the mean, minimum, and maximum elapsed CPU cycles. Use the minimum value for the overhead adjustment (TSCCYCLES) in tsc.h.
 */

#include "tsc.h"

int main() {
    eval_tsc_cycles();
    return 0;
}
