#include "psomm.h"


typedef struct {
     double position[MAX_LENGTHS]; //should be array n dimension
     double velocity[MAX_LENGTHS]; //should also be array n dimension
     double fitness;
     double best_fitness;
     double *best_position;
} particle;


#define W_WAIST_SIZE 1
#define W_REAL 10
#define W_IMAG 1


typedef struct {
     int f1;
     int f2;
     double w1;
     double w2;
} constants;

constants dat;




particle swarm[NUM_PARTICLES];

double inertial_weight;
int max_iterations = MAX_ITERATIONS;
int num_particles = NUM_PARTICLES;
int domain_max, domain_min;



typedef double evaluation(particle *);


evaluation (* fitness)(particle *p){
     int L1, L2, L3;
     int f1, f2;
     double w1, w2;
     
     L1 = p->position[0];
     L2 = p->position[1];
     L3 = p->position[2]; 
     f1 = dat.f1;
     f2 = dat.f2;
     w1 = dat.w1;
     q1 = q(w1);
     q2 = two_lens(L1, L2, L3, f1, f2, q1);

     w2_calc = w_q(q2);
     q_target = q(w2);     
     return W_WAIST_SIZE*(w2_calc - w2) + W_REAL*(1-fabs(creal(q2))) + W_IMAG*(cimag(q_target) - cimag(q2));
}


void pso_solve(const double w1, const double w2, const double f1, const double f2,const double L) {
     int i, j;
     particle *p;
     double weight_decay = 0.6 / max_iterations;

     srand(time(NULL));

     domain_min = 0;
     domain_max = L;


     dat.w1 = w1; dat.w2 = w2; dat.f1 = f1; dat.f1 = f2;
     inertial_weight = 1;

     initialize_swarm(&swarm, num_particles);


     /* Main Loop */
     for ( i = 0; i < max_iterations; i++) {
          for (j = 0; j < num_particles; j++) {
               p = &swarm[j];
               update_velocity(p);
               update_position(p);
               evaluate(p);
          }         
          inertial_weight -= weight_decay;
     }

     print_status();
     printf("Done..\n");

     return 0;
}


