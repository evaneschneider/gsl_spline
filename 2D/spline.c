#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>

int main()
{
  int i, xi, yi;
  int N = 200;

  double *n_arr;
  double *T_arr;
  double *L_arr;
  double *H_arr;
  double *za; 

  int nx = 81;
  int ny = 41;
  double xa[nx], ya[ny];
  za = (double *) malloc(nx*ny*sizeof(double));
  
  FILE *infile;
  char buffer[0x1000];
  char * pch;  

  const gsl_interp2d_type *T = gsl_interp2d_bilinear;
  gsl_spline2d *C_spline = gsl_spline2d_alloc(T, nx, ny);
  gsl_spline2d *H_spline = gsl_spline2d_alloc(T, nx, ny);
  gsl_interp_accel *xacc = gsl_interp_accel_alloc();
  gsl_interp_accel *yacc = gsl_interp_accel_alloc();

  n_arr = (double *) malloc(nx*ny*sizeof(double));
  T_arr = (double *) malloc(nx*ny*sizeof(double));
  L_arr = (double *) malloc(nx*ny*sizeof(double));
  H_arr = (double *) malloc(nx*ny*sizeof(double));  

  // Read in low T cooling curve (function of density and temperature)
  i=0;
  infile = fopen("cloudy_coolingcurve_lowT.txt", "r");
  if (infile == NULL) {
    printf("Unable to open Cloudy file.\n");
    exit(1);
  }
  while (fgets(buffer, sizeof(buffer), infile) != NULL)
  {
    if (buffer[0] == '#') {
      continue;
    }
    else {
      pch = strtok(buffer, "\t");
      n_arr[i] = atof(pch);
      while (pch != NULL)
      {
        pch = strtok(NULL, "\t");
        if (pch != NULL)
          T_arr[i] = atof(pch);
        pch = strtok(NULL, "\t");
        if (pch != NULL)
          L_arr[i] = atof(pch);
        pch = strtok(NULL, "\t");
        if (pch != NULL)
          H_arr[i] = atof(pch);
      }
      i++;
    }
  }
  fclose(infile);

  // Set x and y values
  for (xi=0; xi<nx; xi++) {
    xa[xi] = -4.0 + 0.1*xi;
  }
  for (yi=0; yi<ny; yi++) {
    ya[yi] = 1.0 + 0.1*yi;
  }
  
  // Set z grid values for cooling interpolation 
  for (xi=0; xi<nx; xi++) {
    for (yi=0; yi<ny; yi++) {
      gsl_spline2d_set(C_spline, za, xi, yi, L_arr[yi + ny*xi]);
    }
  }

  /* initialize interpolation */
  gsl_spline2d_init(C_spline, xa, ya, za, nx, ny);

  // Set z grid values for heating interpolation
  for (xi=0; xi<nx; xi++) {
    for (yi=0; yi<ny; yi++) {
      gsl_spline2d_set(H_spline, za, xi, yi, H_arr[yi + ny*xi]);
    }
  }

  /* initialize interpolation */
  gsl_spline2d_init(H_spline, xa, ya, za, nx, ny);


  /* interpolate N values in y and print out curve for plotting */
  for (yi = 0; yi < N; yi++)
  {
    double yj = 1.0 + yi*(4.0/(N-1));
    double Ctest = gsl_spline2d_eval(C_spline, -3.0, yj, xacc, yacc);
    double Htest = gsl_spline2d_eval(H_spline, -3.0, yj, xacc, yacc);
    printf("%f %f %f\n", yj, Ctest, Htest);
  }

  gsl_spline2d_free(C_spline);
  gsl_spline2d_free(H_spline);
  gsl_interp_accel_free(xacc);
  gsl_interp_accel_free(yacc);
  free(n_arr);
  free(T_arr);
  free(L_arr);
  free(H_arr);
  free(za);  

  return 0;
}
