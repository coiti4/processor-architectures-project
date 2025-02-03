/*!
 * \file power_naive.s
 * \brief Naïve exponentiation in MIPS assembly.
 *
 * w = 1;
 * For i in [1..n]:
 *    w *= x
 */

        .data
x:      .double 2.0
w:      .double 1.0
n:      .word   5

        .text
main:
        ld    r1, n(r0)     # r1 = exponent
        l.d   f1, x(r0)     # base
        l.d   f2, w(r0)     # accumulator = 1
loop:
        mul.d f2, f2, f1    # multiply result by base
        daddi r1, r1, -1
        bne   r0, r1, loop
        s.d   f2, w(r0)
        halt
