#include "direct_solve.h"
#define ERROR 1

extern double wavelength;


void direct_solve(const double w1, const double w2, const int f1, const int f2, const double L) {

     double L1avg, L2avg, L3avg, wavg, w2_calc, count;
     int L1, L2, L3, Leff, L1sum, L2sum, L3sum, wsum, lower, upper;

     count = lower = upper = L1sum = L2sum = L3sum = wsum = 0;

     double complex q1, q_target, q2;

     q1 = q(w1);
     q_target = q(w2);
     Leff = L;
     for(L1=0; L1 < Leff; L1++) {
          for(L3=0; L3<Leff-L1; L3++) {
               L2 = Leff-L1-L3;
               q2 = two_lens(L1, L2, L3, f1, f2, q1);
               w2_calc = w_q(q2);

               if (eq(cimag(q2),cimag(q_target))) {
                    if ((fabs(creal(q2)) < ERROR) && eq(w2,w2_calc)) {
                         if (L1 > lower && L2 > 8 && L3 > upper ) {
                                   wsum += w2_calc; L1sum += L1; L2sum += L2; L3sum += L3;
                                   count ++;
                         }
                    }
               }
          }
     }

     if (count) {
          L1avg = L1sum/count; L2avg = L2sum/count; L3avg = L3sum/count; wavg = wsum/count;
          printf("f1: %d   f2: %d    L1: %6.0f   L2: %6.0f  L3:  %6.0f  waist:  %6.2f um   count: %5.0f\n", f1, f2, L1avg, L2avg, L3avg, wavg, count); 
     }

}


int load_bank(int ***bank) {
     FILE *fp;
     int  f1, f2, nrows, i;
   
     if ((fp = fopen("bank", "r"))) {
          fscanf(fp, "%d", &nrows);

          *bank = (int **)malloc(nrows * sizeof(int *));
          for(i = 0; i < nrows; i++) {
               (*bank)[i] = (int *)malloc(2 * sizeof(int));
          }
          for(i=0; i < nrows; i++) {
               fscanf(fp, "%d %d", &f1, &f2);
               (*bank)[i][0] = f1;
               (*bank)[i][1] = f2;
          }
          fclose(fp);
     }
     return nrows;
}




int main(int argc, char **argv) {
     double w1, w2, L;
     int f1,f2, num,i;
     int **bank;
     printf("Direct Solving...\n"); 
     num = load_bank(&bank);
     
     w1 = 200;
     w2 = 200; 
     L = 600;

     for(i=0; i<num; i++) {
          f1 = bank[i][0];
          f2 = bank[i][1];
          direct_solve(w1, w2, f1, f2, L);     
     }
     
     return 0;
}













        
/*
  Test Cases:

     printf("Waist 1 size: %f um\n", w1); 
     q1 = q(w1);
     w2 = w_q(q1);
     printf("Waist 2 size: %f um\n", w2); 


     printf("z_w 300 -> 332.0:  %f\n", z_w(300)); 
     printf("Waist_z 500 -> 368.0: %f\n", waist_z(500)); 
     printf("W_z 400,100  -> 787.0 %f\n", w_z(400, 1000)); 
     printf("R_z 400, 1000 -> 1347.99161 %f\n", R_z(400,1000)); 
     printf("Q 400 -> 589.908137139j  %g + %gj\n", creal(q(400)), cimag(q(400)));
     printf("q_z 400, 1000 -> 1000 + 589.908137139j  %g + %gj\n", creal(q_z(400,1000)), cimag(q_z(400,1000))); 
     printf("w_q w_q(q_z(400, 100)) -> 400.0    %f\n", w_q(q_z(400,100))); 


*/
