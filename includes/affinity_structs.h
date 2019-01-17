#ifndef __AFFINITY_STRUCTS_H__
#define __AFFINITY_STRUCTS_H__

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

#include "macros.h"

typedef struct update_str 
{
  int *left_border;
  int **chunksize;
  int *chunk_index;
  int *chunk_count;
} s_str;

#endif //__AFFINITY_STRUCTS_H__