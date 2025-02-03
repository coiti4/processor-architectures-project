/*!
 * \file mulf.s
 * \brief Single-precision float multiplication in MIPS assembly.
 */

        .data
A:      .float 5.0
B:      .float 7.0
C:      .float 0.0

        .text
main:
        l.s   $f0, A($zero)
        l.s   $f1, B($zero)
        mul.s $f2, $f0, $f1
        s.s   $f2, C($zero)
        halt
