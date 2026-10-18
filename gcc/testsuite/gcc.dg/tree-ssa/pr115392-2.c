/* PR tree-optimization/115392 */
/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

/* ge with low bit of C set: b = 2 gives (b|1) >= 3 true but b >= 3 false.  */
_Bool n1(unsigned b) { return (b | 1) >= 3; }

/* lt with low bit of C set: b = 2 gives (b|1) < 3 false but b < 3 true.  */
_Bool n2(unsigned b) { return (b | 1) < 3; }

/* le with low 5 bits of C not all set.  */
_Bool n3(unsigned b) { return (b ^ 0x12) <= 0xE0; }

/* { dg-final { scan-tree-dump-times " \\| " 2 "optimized" } } */
/* { dg-final { scan-tree-dump-times " \\^ " 1 "optimized" } } */
