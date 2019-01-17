# openmp_affinity
using OpenMP to parallelize the given code with user-defined 'affinity' scheduling.

This is a practical project for how to finish a real coursework, there are three main objects about this project:
- `How to construct/re-construct a real C program project.`
- `How to use Makefile to do auto testing, including frontend and backend(CIRRUS)`
- `Investigating the efficiency of custom schediling 'Affinity' and other built-in schedulings.`

### what is included at this C program project
```
├── Makefile
├── README.md
├── bin
│   ├── affinity
│   ├── best_schedule_loop_1
│   ├── best_schedule_loop_2
│   ├── runtime
│   └── serial
├── includes
│   ├── affinity_structs.h
│   ├── macros.h
│   └── resource.h
├── obj
│   ├── affinity.o
│   ├── main.o
│   ├── mem.o
│   ├── omplib.o
│   └── workload.o
├── out
├── res
│   ├── efficiency.eps
│   ├── execution_time_loop1.eps
│   ├── execution_time_loop2.eps
│   ├── speed_up.eps
│   └── test_results.csv
├── scripts
│   ├── autotest.sh
│   ├── autotest_backend.pbs
│   └── plot.py
└── src
    ├── affinity
    │   ├── affinity.c
    │   └── affinity.h
    ├── loops
    │   ├── workload.c
    │   └── workload.h
    ├── main.c
    ├── omplib
    │   ├── omplib.c
    │   └── omplib.h
    └── utils
        ├── mem.c
        └── mem.h
```
