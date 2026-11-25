/* PR tree-optimization/128948 */
/* { dg-do compile { target { sse2 || riscv_v } } } */
/* { dg-additional-options "-msse2" { target sse2 } } */
/* { dg-additional-options "-fdump-tree-optimized" } */

void
sat_add_imm_i8 (signed char *out, const signed char *in, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      signed char x = in[i];
      signed char sum = (unsigned char) x + 6;
      out[i] = (x ^ 6) < 0 || (x ^ sum) >= 0
	       ? sum : x < 0 ? -128 : 127;
    }
}

void
sat_add_imm_i16 (short *out, const short *in, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      short x = in[i];
      short sum = (unsigned short) x + 9;
      out[i] = (x ^ 9) < 0 || (x ^ sum) >= 0
	       ? sum : x < 0 ? -32768 : 32767;
    }
}

/* Match the broadcast immediates so a scalar .SAT_ADD cannot satisfy either
   scan.  */
/* { dg-final { scan-tree-dump {\.SAT_ADD \(vect_[^,]*, . 6[, ]} "optimized" } } */
/* { dg-final { scan-tree-dump {\.SAT_ADD \(vect_[^,]*, . 9[, ]} "optimized" } } */
