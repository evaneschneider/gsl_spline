#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

int main (void)
{
  int i;
  double xi, yi, T_arr[41], L_arr[41];

  FILE *infile;
  char buffer[0x1000];
  char * pch;
  char * T;
  char * L;

  i=0;
  infile = fopen("coolingcurve_HM05_n0.txt", "r");
  if (infile == NULL) {
    printf("Unable to open file.\n");
    exit(1);
  }
  while (fgets(buffer, sizeof(buffer), infile) != NULL)
  {
    if (buffer[0] == '#') continue;
    pch = strtok(buffer, "\t");
    T_arr[i] = atof(pch);
    while (pch != NULL)
    {
      pch  = strtok(NULL, "\t");
      if (pch != NULL)
        L_arr[i] = atof(pch); 
    }
    i++;
  }
  fclose(infile);

  {
    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, 41);

    gsl_spline_init(spline, T_arr, L_arr, 41);

    for (xi = T_arr[0]; xi < T_arr[40]; xi += 0.1)
    {
      yi = gsl_spline_eval(spline, xi, acc);
      printf("%g %g\n", xi, yi);
    }
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
  }
  return 0;

}
