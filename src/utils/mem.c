#include "mem.h"

int malloc_chunk_str(int total_threads, s_str *s)
{
      int each_reamin_iter = (int) ceil((double)N/(double)total_threads); 
      int i,j;
      MALLOC(s->chunk_index, total_threads, int);
      MALLOC(s->chunk_count, total_threads, int);
      MALLOC(s->left_border, total_threads, int);
      MALLOC2D(s->chunksize, total_threads, int);

      for(i=0; i<total_threads; i++){
      	MALLOC((s->chunksize)[i], each_reamin_iter, int);  	
      }
      for(i=0;i<total_threads;i++){
      	for(j=0; j<each_reamin_iter; j++){
	  		(s->chunksize)[i][j] = 0;
      	}
    }
    return 0;
}

int free_chunk_str(int total_threads, s_str *s)
{
	int i;
	for(i=0; i<total_threads; i++){
		FREE(s->chunksize[i]);
	}
	FREE(s->chunksize);
	FREE(s->chunk_index);
	FREE(s->left_border);

      return 0;
}