/*!
 * \file abs.s
 * \brief Double-precision absolute value in MIPS assembly.
 *
 * Checks if a number is negative. If so, computes -A1. Otherwise returns A1.
 */

        .data
A1:     .double -10.0
B1:     .double 0.0
zero:   .double 0.0

        .text
main:
        l.d   f2, A1(r0)      # f2 = A1
        l.d   f0, zero(r0)    # f0 = 0.0
        mov.d f4, f2          # f4 = A1
        c.lt.d 7, f2, f0      # compare (f2 < 0 ?)
        bc1f   7, done        # if not negative, skip
        sub.d  f4, f0, f2     # f4 = 0.0 - A1 => |A1|
done:
        s.d   f4, B1(r0)
        halt
