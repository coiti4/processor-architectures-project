/*!
 * \file power_binary.s
 * \brief Binary exponentiation (exponent by squaring) in MIPS assembly.
 *
 * More efficient exponent: O(log n).
 */

        .data
x:      .double 2.0
w:      .double 1.0
n:      .word   5

        .text
main:
        ld    r1, n(r0)     # r1 = exponent
        addi  r2, r0, 1     # mask for bit test
        l.d   f1, x(r0)     # base
        l.d   f2, w(r0)     # result=1
loop:
        and   r3, r2, r1    # check LSB of exponent
        dsrl  r1, r1, 1     # shift exponent right
        beq   r3, r0, endif
        mul.d f2, f2, f1
endif:
        mul.d f1, f1, f1
        bne   r0, r1, loop
        s.d   f2, w(r0)
        halt
