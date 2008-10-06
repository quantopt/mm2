#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include "randvar.h"



#define UNFIT 1000
#define NUM_PARTICLES 10
#define MAX_ITERATIONS 100
#define VELOCITY_MIN -1
#define VELOCITY_MAX 1
#define MAX_LENGTHS 3


extern struct particle;

/* particle pouplation, swarm size, domain min, domain max */
void initialize_particle(particle *);
void initialize_swarm(particle[], int);
void update_velocity(particle *);
void update_position(particle *);
void evaluate(particle *);   //send function pointer 4 eval function
void print_status(void);



