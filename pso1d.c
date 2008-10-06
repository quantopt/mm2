/* Sidney Burks

   Canonical Particle Swarm Optimization  code

   August 12, 2008
*/

#include "pso.h"

double gbest_fitness;
double gbest_position[MAX_LENGTHS];


void initialize_swarm(particle *swarm, int num_particles)
{
     int i;
     particle *p;
     for (i = 0; i < num_particles; i++) {
          p = &swarm[i];
          initialize_particle(p);
     }
}

char is_valid_position(int position) {
     char state=1; 
     int i;
     
     for(i=0; i<MAX_LENGTHS; i++){
          state = (position >domain_min) && (position < domain_max);
          if (!state) {
               break;
          }
     }

     return state;
}

int get_random_position(int *position) {
     int i;
     for(i=0; i<MAX_LENGTHS; i++){
          do {
               position[i] = uniform(domain_min, domain_max);
          } while (!is_valid_position(position[i]));
     }
     return position;
}

void initialize_particle(particle *p){
     get_random_position(p->position);
     p->velocity = uniform(VELOCITY_MIN, VELOCITY_MAX);
     p->fitness = UNFIT;
     p->best_fitness = p->fitness; 
     p->best_position = p->position;
}




void update_velocity(particle  *p) {
     /* PSO specific velocity update equation */
     double phi1 = uniform(0,2);
     double phi2 = uniform(0,2);
     int i;

     for(i=0; i<MAX_LENGTHS; i++) {
          p->velocity[i] = inertial_weight*p->velocity[i] + phi1*(p->best_position[i]-p->position[i]) + phi2*(gbest_position[i]-p->position[i]);
     }
}

void update_position(particle  *p) {
     /* Updates particle position vector:  x(i+1) = x(i) + v(i+1)   */

     for (i=0; i<MAX_LENGTHS; i++) {
          p->position[i] = p->position[i] + p->velocity[i];
          if (!is_valid_position(p->position[i]))
               initialize_particle(p);
     }
}



void evaluate(particle  *p, evaluation *function) {
     /* returns the value of the objective function when evaluated at its  position 
        returns f(x) given x 
        Also updates particle best position and fitness, and global bests if  necessary 
       
     */

     p->fitness = function(p);

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


