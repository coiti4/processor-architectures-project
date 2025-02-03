/*!
 * \file sumf.s
 * \brief Single-precision float addition in MIPS assembly.
 *
 * Loads two floats, adds them, stores the result.
 * Demonstrates pipeline stalls for floating-point operations.
 */

        .data
A:      .float 5.0
B:      .float 7.0
C:      .float 0.0

        .text
main:
        l.s  $f0, A($zero)    # $f0 = A
        l.s  $f1, B($zero)    # $f1 = B
        add.s $f2, $f0, $f1   # $f2 = A + B
        s.s  $f2, C($zero)    # C = A + B
        halt
