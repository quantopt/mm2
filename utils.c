#include "utils.h"

char eq(const double a,const double b) {
     int tolerance = 1;
      return (abs(a-b) < tolerance);
}
