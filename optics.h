#include "utils.h"
#include <complex.h>
#include <math.h>

#define pi M_PI
#define wavelength 0.85209000000000000

#define up(x) ((x)/1000.0)
#define down(x) ((x)*1000.0)

#define n2u(x) up((x))
#define m2u(x) down((x))
#define u2m(x) up((x))


char eq(const double, const double);


double complex q(const double);

double complex q_z(const double, const double);

double R_z(const double, const double);

double waist_z(const double);

double w_q(const double complex);

double w_z(const double, const double);

double z_w(const double);
