/*!
 * \file double.s
 * \brief Combined double-precision operations in MIPS assembly.
 *
 * Performs addition, multiplication, and division on pairs of doubles
 * (A1,B1) and (A2,B2), storing results in C1, C2.
 */

        .data
A1:     .double 2.0
B1:     .double 3.0
C1:     .double 0.0
A2:     .double 10.0
B2:     .double 5.0
C2:     .double 0.0

        .text
main:
    # 1) C1=A1+B1  C2=A2+B2
    l.d   f0,A1(r0)
    l.d   f4,B1(r0)
    l.d   f2,A2(r0)
    l.d   f6,B2(r0)
    add.d f8,f0,f4
    add.d f10,f2,f6
    s.d   f8,C1(r0)
    s.d   f10,C2(r0)

    # 2) C1=A1*B1  C2=A2*B2
    l.d   f0,A1(r0)
    l.d   f2,A2(r0)
    l.d   f4,B1(r0)
    l.d   f6,B2(r0)
    mul.d f8,f0,f4
    mul.d f10,f2,f6
    s.d   f8,C1(r0)
    s.d   f10,C2(r0)

    # 3) C1=A1/B1  C2=A2/B2
    l.d   f0,A1(r0)
    l.d   f4,B1(r0)
    div.d f8,f0,f4
    l.d   f2,A2(r0)
    l.d   f6,B2(r0)
    div.d f10,f2,f6
    s.d   f8,C1(r0)
    s.d   f10,C2(r0)
    halt
