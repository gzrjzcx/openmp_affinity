#ifndef __WORKLOAD_H__
#define __WORKLOAD_H__

void init1(void);
void init2(void);
void runloop(int); 
void loop1chunk(int, int);
void loop2chunk(int, int);
void valid1(void);
void valid2(void);
void execute_loop(int loopid, int iter_start, int iter_end);

#endif //__WORKLOAD_H__