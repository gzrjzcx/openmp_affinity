#include <stdio.h>
#include <math.h>
#include <omp.h>

#include "resource.h"
#include "workload.h"
#include "omplib.h"

#ifdef AFFINITY
  #include "affinity.h"
#endif

int main(int argc, char *argv[]) { 

  double start1,start2,end1,end2;
  int r;

  init1(); 

  start1 = gettime(); 

  for (r=0; r<reps; r++){ 
#ifdef AFFINITY
    runloop_affinity(1);
#else
    runloop(1);
#endif
  } 

  end1  = gettime();  

  valid1(); 

  printf("Total time for %d reps of loop 1 = %f\n",reps, (float)(end1-start1)); 


  init2(); 

  start2 = gettime(); 

  for (r=0; r<reps; r++){ 
#ifdef AFFINITY
    runloop_affinity(2);
#else
    runloop(2);
#endif
  } 

  end2  = gettime(); 

  valid2(); 

  printf("Total time for %d reps of loop 2 = %f\n",reps, (float)(end2-start2)); 

} 