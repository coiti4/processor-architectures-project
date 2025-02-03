/*!
 * \file mul.s
 * \brief Integer multiplication in MIPS assembly.
 *
 * Loads two integers, multiplies them, and stores the product.
 * Some MIPS variants require separate mult/mflo instructions.
 */

        .data
A:      .word 5
B:      .word 7
C:      .word 0

        .text
main:
        lw   $t0, A($zero)
        lw   $t1, B($zero)
        mul  $t2, $t0, $t1   # $t2 = A * B
        sw   $t2, C($zero)
        halt
