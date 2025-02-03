/*!
 * \file sum.s
 * \brief Simple integer addition in MIPS assembly (pipeline example).
 *
 * This program loads two integers from memory, sums them,
 * and stores the result back to memory. Useful for demonstrating
 * basic integer pipeline behavior (e.g. stalls, forwarding).
 */

        .data
A:      .word 5
B:      .word 7
C:      .word 0

        .text
main:
        lw   $t0, A($zero)    # $t0 = A
        lw   $t1, B($zero)    # $t1 = B
        add  $t2, $t0, $t1    # $t2 = A + B
        sw   $t2, C($zero)    # C = A+B
        halt                  # End of program
