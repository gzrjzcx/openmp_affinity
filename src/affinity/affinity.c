#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "affinity.h"
#include "affinity_structs.h"
#include "resource.h"
#include "workload.h"
#include "omplib.h"
#include "mem.h"

/* Non-global functions are defined at implementation file */
/* Global functions are defined at head file */
int set_chunksize(int left_border, int right_border, int total_threads, int thread_id,\
 s_str *s);
int get_nextwork_thread(int loopid, int total_threads, int thread_id, s_str *s,int *iter_start, int *iter_end);
int find_most_loaded_thread(int loopid, int total_threads, int thread_id, s_str *s);
void execute_next_chunksize(int loopid, int thread_id, int next_work_thread, s_str *s,int *iter_start, int *iter_end);

void runloop_affinity(int loopid)
{
	int total_threads = get_total_threads();
	s_str s;

	malloc_chunk_str(total_threads, &s);

	#pragma omp parallel default(none) shared(loopid, total_threads, s)
	  {
	    int myid  = get_current_tid();
	    int nthreads = get_total_threads();
	    int left_border, right_border;

	    int ipt = (int) ceil((double)N/(double)nthreads); 
	    int lo = myid*ipt;
	    if (lo > N) lo = N;
	    int hi = (myid+1)*ipt;
	    if (hi > N) hi = N;
	    int iter_start, iter_end;
	    iter_start = iter_end = 0;
	    left_border = lo;
	    right_border = hi;  
	    int next_work_thread = 0;
	    set_chunksize(left_border, right_border, total_threads, myid, &s);
	    #pragma omp barrier 

	 
	    while(next_work_thread != -1)
	    {
	      execute_loop(loopid, iter_start, iter_end);
	      #pragma omp critical
	      { 
	        next_work_thread = get_nextwork_thread(loopid, total_threads, myid, &s, &iter_start, &iter_end);
	      }
	    }
	  }

	  free_chunk_str(total_threads, &s);
}

int set_chunksize(int left_border, int right_border, int total_threads, \
	int thread_id, s_str *s){

  int count = 0;
  int index = 0;
  int i;
  int *left, *right;
  int initial_leftboard =  left_border;
  int total_remain_iter = right_border - initial_leftboard;
  
  while(left_border < right_border){
    int remain_iter_num = right_border - left_border;

    if(remain_iter_num < total_threads){
      (s->chunksize)[thread_id][index] = remain_iter_num;
    }
    else{
      (s->chunksize)[thread_id][index] = (int)ceil((double)(remain_iter_num)/(double)total_threads);
    }

    if((s->chunksize)[thread_id][index] > remain_iter_num){
      (s->chunksize)[thread_id][index] = remain_iter_num;
    }

    left_border += (s->chunksize)[thread_id][index];
    count += (s->chunksize)[thread_id][index];

    index++;
  }

  s->left_border[thread_id] = initial_leftboard;

/* invert index to be easy to detect if a local task is finished */
  	  left = (s->chunksize)[thread_id];
	  right = &(s->chunksize)[thread_id][index-1];
	  while(left < right)
	  {
		*left  ^= *right;
		*right ^= *left;
		*left  ^= *right;

		left++;
		right--;
	  }
  s->chunk_index[thread_id]=index-1;
  return 1;
}

int get_nextwork_thread(int loopid, int total_threads, int thread_id, s_str *s, int *iter_start, int *iter_end)
{
	int next_work_thread = -1;
	if(s->chunk_index[thread_id]>=0)
	{
		next_work_thread = thread_id;
	}
	else
	{
		next_work_thread = find_most_loaded_thread(loopid, total_threads, thread_id, s);
	}

	if(next_work_thread == -1)
	{
		return -1;
	}

	execute_next_chunksize(loopid, thread_id, next_work_thread, s, iter_start, iter_end);
	return 1;
}

int find_most_loaded_thread(int loopid, int total_threads, int thread_id, s_str *s)
{
	int i;
	int most_loaded_therad = -1;
	int max_index = 0;
	for(i=0; i<total_threads; i++)
	{
		if(s->chunk_index[i] > max_index)
		{			
			max_index = s->chunk_index[i];
			most_loaded_therad = i;
		}
	}
	return most_loaded_therad;
}

void execute_next_chunksize(int loopid, int thread_id, int next_work_thread, s_str *s, int *iter_start, int *iter_end)
{
	*iter_start = s->left_border[next_work_thread];
	*iter_end = *iter_start + s->chunksize[next_work_thread][s->chunk_index[next_work_thread]];
	s->chunk_index[next_work_thread]--;
	s->left_border[next_work_thread] = *iter_end;
}