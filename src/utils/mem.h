#ifndef __MEM_H__
#define __MEM_H__

#include "resource.h"
#include "affinity_structs.h"

int malloc_chunk_str(int total_threads, s_str *s);
int free_chunk_str(int total_threads, s_str *s);

#endif //__MEM_H__