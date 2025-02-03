/*!
 * \file fib.s
 * \brief Fibonacci sequence in MIPS assembly.
 *
 * Demonstrates loop iteration, basic integer ops, and pipeline stalls
 * for load-dependencies and branching.
 */

        .data
fibs:   .word 0:50       # space for fib sequence
size:   .word 12         # compute first 12 fib numbers

        .text
main:
        addi  $t0, $zero, fibs  # address of the array
        addi  $t2, $zero, 1
        lw    $t5, size($zero)  # number of fib elements
        sw    $t2, 0($t0)       # F[0] = 1
        sw    $t2, 4($t0)       # F[1] = 1
        addi  $t1, $t5, -2      # number left = (N-2)
loop:
        lw    $t3, 0($t0)       # F[n]
        lw    $t4, 4($t0)       # F[n+1]
        addi  $t0, $t0, 4       # move pointer
        add   $t2, $t3, $t4     # next fib = F[n]+F[n+1]
        addi  $t1, $t1, -1
        sw    $t2, 4($t0)       # store in F[n+2]
        bnez  $t1, loop
        nop
        halt
