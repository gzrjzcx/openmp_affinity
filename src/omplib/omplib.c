#include <stdio.h>
#include <omp.h>

int get_total_threads(){
	char *s=getenv("OMP_NUM_THREADS");	
	int total_threads = atoi(s);
	return total_threads;
}

int get_current_tid(){
	return omp_get_thread_num();
}

double gettime(void)
{
	return omp_get_wtime();
}