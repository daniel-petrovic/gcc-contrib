/* PR tree-optimization/115392 */
/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

/* Case 1: low m bits of C all set, le/gt.  */
_Bool f1(unsigned b) { return (b | 0x12) <= 0xFF; }
_Bool f2(unsigned b) { return (b ^ 0x12) > 0xFF; }

/* Case 2: low m bits of C all clear, lt/ge.  */
_Bool f3(unsigned b) { return (b | 0x12) < 0x100; }
_Bool f4(unsigned b) { return (b ^ 0x12) >= 0x100; }

/* Original report: a has range [0,1].  */
_Bool f5(unsigned b, _Bool a) { return (b ^ a) <= 3; }

/* Signed type, constant cannot touch the sign bit.  */
_Bool f6(int b) { return (b | 0x12) <= 0xFF; }

/* { dg-final { scan-tree-dump-not " \\| " "optimized" } } */
/* { dg-final { scan-tree-dump-not " \\^ " "optimized" } } */
