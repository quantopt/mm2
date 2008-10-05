#include "optics.h"
 
double waist_z(const double z) {
     return sqrt(m2u(z)*wavelength/pi);
}


double w_z(const double w0, const double z) {
     return w0*sqrt(1+pow(z/z_w(w0),2));
}

double R_z(const double w, const double z) {
          return z*(1+pow(z_w(w)/z,2));
}

double complex q(const double w) {
     return z_w(w)*I;
}

double complex q_z(const double w, const double z) {
     return z + z_w(w)*I;
}

double w_q( const double complex q) {
     return waist_z(cimag(q));
}

double  z_w(const double waist) {
     return ((pi*pow(u2m(waist),2))/u2m(wavelength));
}


char eq(const double a,const double b) {
     int tolerance = 1;
      return (fabs(a-b) < tolerance);
}
