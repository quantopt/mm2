#include "matrices.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


#define DIM 2


typedef double matrix[2][2];

typedef struct {
     matrix mat;
     void (* function)(matrix *, const double);
} element;

void identity(matrix *m, const double d) {
    *m[0][0] = 1;  *m[0][1] = 0;
    *m[1][0] = 0;  *m[1][1] = 1;
}

void distance(matrix *m, const double d) {
     *m[0][0] = 1;  *m[0][1] = 2;
     *m[1][0] = 3;  *m[1][1] = 4;
}

void lens(matrix *m, const double f) {
     *m[0][0] = 1;  *m[0][1] = 0;
     *m[1][0] = -1/f;  *m[1][1] = 1;
}

void mirror(matrix *m, const double r){
     *m[0][0] = 1;  *m[0][1] = 0;
     *m[1][0] = 2/r;  *m[1][1] = 1;
}

void mmul(matrix *res, const matrix *a, const matrix *b){
     int i,j,k;
     for (i=0; i<DIM; i++) {
          for(j=0; j<DIM; j++) {
               *res[i][j] = 0;
               printf("%d %d %d %f\n",i,j,k, (*a)[i][j]); 
               printf("%f \n", (*a)[0][1]); 

               /* for(k=0; k<DIM; k++){ */
               /*      printf("%d %d %d %f\n",i,j,k, (*b)[i][j]);  */

               /*      *res[i][j] = *a[i][j];//\*(*b[k][j]); */
               /* } */
          }
     }
     puts("Returning...");
}

void show(matrix *a) {
     printf("%f   %f\n", *a[0][0], *a[0][1]); 
     printf("%f   %f\n", *a[1][0], *a[1][1]); 
}


/* matrix *process_chain(matrix path[], matrix *res) { */
/*      int i, length; */
/*      matrix temp = {{1,0},{0,1}}; */
/*      length=sizeof(path)/sizeof(matrix); */
/*      for(i=0; i<length; i++) { */
/*           temp = mmul(temp, path[i]); */
/*      } */
/*      return &temp; */
/* } */

int main(int argc, char **argv) {
     element *path;
     char* pathstr = "DLDLD";
     char *tmp;
     int i;
     int length = strlen(pathstr);
     matrix result, self;

     path = (element *) malloc(length * sizeof(element));

     for (i=0; i<length; i++) {
          printf("%c\n", pathstr[i]);
          switch (pathstr[i]) {
          case 'D':
               path[i].function = &distance;
               break;
          case 'L':
               path[i].function = &lens;
               break;
          case 'M':
               path[i].function = &mirror;
              break;
          default:
                  break;
          }
          //path[i].mat = (matrix *) malloc(sizeof(matrix));
          (* path[i].function)(&path[i].mat, 100);
          printf("Path %d\n", i); 

          show(&path[i].mat);
     }

     //     result = path[0].mat;
     printf("path0:\n");
     printf("%d   %d\n", (path[0].mat)[0][0], (path[0].mat)[0][1]); 
     printf("%d   %d\n", path[0].mat[1][0], path[0].mat[1][1]); 

     show(&path[0].mat);
     exit(1);
     mmul(&result, &path[0].mat, &self);


     identity(&self, 0);
     printf("Identity:\n");
     show(self);

     printf("path0:\n");
     show(path[0].mat);
    
     mmul(&result, &path[0].mat, &self);

     printf("Result:\n");

     show(result);
     free(path);
     return 0;
}


/* distance(d) */
/* //refraction_flat (n1,n2) */
/* //refraction_curved(n1,n2,R) */
/* mirror(r) */
/* lens(f) */

