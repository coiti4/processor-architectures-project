/*!
 * \file divf.s
 * \brief Single-precision float division in MIPS assembly.
 *
 * Demonstrates pipeline stalls for floating-point divide.
 */

        .data
A:      .float 10.0
B:      .float 2.0
C:      .float 0.0

        .text
main:
        l.s   $f0, A($zero)
        l.s   $f1, B($zero)
        div.s $f2, $f0, $f1   # $f2 = A / B
        s.s   $f2, C($zero)
        halt
