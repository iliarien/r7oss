/* Test file for mpfr_cot.

Copyright 2005, 2006, 2007, 2008 Free Software Foundation, Inc.
Contributed by the Arenaire and Cacao projects, INRIA.

This file is part of the MPFR Library.

The MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPFR Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
MA 02110-1301, USA. */

#include <stdio.h>
#include <stdlib.h>

#include "mpfr-test.h"

#define TEST_FUNCTION mpfr_cot
#define REDUCE_EMAX 262143 /* otherwise arg. reduction is too expensive */
#include "tgeneric.c"

static void
check_specials (void)
{
  mpfr_t  x, y;

  mpfr_init2 (x, 123L);
  mpfr_init2 (y, 123L);

  mpfr_set_nan (x);
  mpfr_cot (y, x, GMP_RNDN);
  if (! mpfr_nan_p (y))
    {
      printf ("Error: cot(NaN) != NaN\n");
      exit (1);
    }

  mpfr_set_inf (x, 1);
  mpfr_cot (y, x, GMP_RNDN);
  if (! mpfr_nan_p (y))
    {
      printf ("Error: cot(Inf) != NaN\n");
      exit (1);
    }

  mpfr_set_inf (x, -1);
  mpfr_cot (y, x, GMP_RNDN);
  if (! mpfr_nan_p (y))
    {
      printf ("Error: cot(-Inf) != NaN\n");
      exit (1);
    }

  /* cot(+/-0) = +/-Inf */
  mpfr_set_ui (x, 0, GMP_RNDN);
  mpfr_cot (y, x, GMP_RNDN);
  if (! (mpfr_inf_p (y) && mpfr_sgn (y) > 0))
    {
      printf ("Error: cot(+0) != +Inf\n");
      exit (1);
    }
  mpfr_neg (x, x, GMP_RNDN);
  mpfr_cot (y, x, GMP_RNDN);
  if (! (mpfr_inf_p (y) && mpfr_sgn (y) < 0))
    {
      printf ("Error: cot(-0) != -Inf\n");
      exit (1);
    }

  mpfr_clear (x);
  mpfr_clear (y);
}

static void
two2emin (mp_exp_t e)
{
  mp_exp_t old_emin, old_emax;
  mpfr_t x, y;
  int i, rnd;

  old_emin = mpfr_get_emin ();
  old_emax = mpfr_get_emax ();

  if (mpfr_set_emin (-e) || mpfr_set_emax (e))
    {
      printf ("Can't change exponent range\n");
      exit (1);
    }

  mpfr_inits2 (53, x, y, (void *) 0);
  for (i = -4; i <= 4; i++)
    RND_LOOP (rnd)
      {
        mpfr_set_si (y, i, GMP_RNDN);
        mpfr_ui_div (y, 1, y, rnd);  /* no overflow/underflow */
        mpfr_set_si_2exp (x, i, -e, GMP_RNDN);
        if (ABS (i) != 3)  /* not a power of 2 (not 0 either) */
          mpfr_sub (y, y, x, rnd);  /* no overflow/underflow */
        mpfr_set_ui_2exp (x, 1, -e, GMP_RNDN);
        mpfr_div (y, y, x, rnd);  /* 1/x - SIGN(x).epsilon */
        mpfr_set_si_2exp (x, i, -e, GMP_RNDN);
        mpfr_cot (x, x, rnd);
        if (! mpfr_equal_p (x, y))
          {
            printf ("Error in two2emin for i = %d and rnd = %s\n",
                    i, mpfr_print_rnd_mode (rnd));
            printf ("Got        ");
            mpfr_dump (x);
            printf ("instead of ");
            mpfr_dump (y);
            exit (1);
          }
      }
  mpfr_clears (x, y, (void *) 0);

  mpfr_set_emin (old_emin);
  mpfr_set_emax (old_emax);
}

int
main (int argc, char *argv[])
{
  tests_start_mpfr ();

  check_specials ();
  two2emin (256);
  two2emin (MPFR_EMAX_DEFAULT);
  if (MPFR_EMAX_MAX != MPFR_EMAX_DEFAULT)
    two2emin (MPFR_EMAX_MAX);
  test_generic (2, 200, 5);

  tests_end_mpfr ();
  return 0;
}
