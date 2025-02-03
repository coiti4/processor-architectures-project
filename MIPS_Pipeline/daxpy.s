/*!
 * \file daxpy.s
 * \brief DAXPY kernel (y[i] = a*x[i] + y[i]) in MIPS assembly.
 *
 * Demonstrates double-precision floating operations and loop iteration.
 */

        .data
A:      .double 2.0
X:      .space 96     # storage for 12 doubles
Y:      .space 96
N:      .word 12

        .text
main:
        l.d   f0, A(r0)     # f0 = a
        ld    r2, N(r0)     # r2 = N
        daddi r3, r0, X     # r3 -> X
        daddi r4, r0, Y     # r4 -> Y
loop:
        l.d   f1, 0(r3)     # f1 = x[i]
        l.d   f2, 0(r4)     # f2 = y[i]
        mul.d f1, f1, f0    # f1 = a*x[i]
        daddi r3, r3, 8
        daddi r4, r4, 8
        daddi r2, r2, -1
        add.d f2, f2, f1    # y[i] += a*x[i]
        s.d   f2, -8(r4)
        bne   r2, r0, loop
        nop
        halt
