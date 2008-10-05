/* Sidney Burks

   Canonical Particle Swarm Optimization  code

   August 12, 2008
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include "randvar.h"

#define func(x) cos(x)*exp(sin(x))*sin(x)/1.5
#define UNFIT 1000
#define NUM_PARTICLES 10
#define MAX_ITERATIONS 100
#define VELOCITY_MIN -1
#define VELOCITY_MAX 1
#define DOMAIN_MIN -4.5
#define DOMAIN_MAX 4.5

static double function(double a)
{
     return func(a);
}

double inertial_weight;
int max_iterations = MAX_ITERATIONS;
int num_particles = NUM_PARTICLES;


double gbest_fitness, gbest_position;

typedef struct {
     double position; //should be array n dimension
     double velocity; //should also be array n dimension
     double fitness;
     double best_fitness;
     double best_position;
} particle;

particle swarm[NUM_PARTICLES];

/* particle pouplation, swarm size, domain min, domain max */
void initialize_particle(particle *);
void initialize_swarm(particle[], int);
void update_velocity(particle *);
void update_position(particle *);
void evaluate(particle *);   //send function pointer 4 eval function
void print_status(void);



void initialize_swarm(particle swarm[], int num_particles)
{
     int i;
     particle *p;
     for (i = 0; i < num_particles; i++) {
          p = &swarm[i];
          initialize_particle(p);
     }
}

void initialize_particle(particle *p){
          p->position = uniform(DOMAIN_MIN, DOMAIN_MAX);
          p->velocity = uniform(VELOCITY_MIN, VELOCITY_MAX);
          p->fitness = UNFIT;
          p->best_fitness = p->fitness; 
          p->best_position = p->position;
}

int main()
{
     srand(time(NULL));

     int i, j;
     particle *p;
     double weight_decay = 0.6 / max_iterations;

     /* here, an intertial weight term is added to teh velocity, and decays as the iterations progress.  It hits a minimum value
        of 0.4, thus going from 1 to 0.4 over the course of the simulation
     */

     inertial_weight = 1;

     initialize_swarm(swarm, num_particles);


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



void update_velocity(particle  *p) {
     /* PSO specific velocity update equation */
     double phi1 = uniform(0,2);
     double phi2 = uniform(0,2);

     p->velocity = inertial_weight*p->velocity + phi1*(p->best_position-p->position) + phi2*(gbest_position-p->position);
}

void update_position(particle  *p) {
     /* Updates particle position vector:  x(i+1) = x(i) + v(i+1)   */

     p->position = p->position + p->velocity;
     if ((p->position < DOMAIN_MIN) || (p->position > DOMAIN_MAX))
          initialize_particle(p);
}



void evaluate(particle  *p) {
     /* returns the value of the objective function when evaluated at its  position 
        returns f(x) given x 
        Also updates particle best position and fitness, and global bests if  necessary 
       
     */

     p->fitness = function(p->position);

     if (p->fitness < p->best_fitness) {
          p->best_fitness = p->fitness;
          p->best_position = p->position;
     }

     if (p->fitness < gbest_fitness) {
          gbest_fitness = p->fitness;
          gbest_position = p->position;
     }
}


void print_status(){
     int i;
     particle *p;
     for (i = 0; i < num_particles; i++) {
          p = &swarm[i];
          printf("Particle %i is at position %4.4f, fitness %4.4f, velocity %4.4f, bestl %4.4f\n", i+1, p->position, p->fitness, p->velocity, p->best_position); 
     }
     printf("Global best fitness is %4.12f at position %4.4f\n", gbest_fitness, gbest_position);

}


