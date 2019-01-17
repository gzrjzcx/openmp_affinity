# openmp_affinity
using OpenMP to parallelize the given code with user-defined 'affinity' scheduling.

This is a practical project for how to finish a real coursework, there are three main objects about this project:
- `How to construct/re-construct a real C program project.`
- `How to use Makefile to do auto testing, including frontend and backend(CIRRUS)`
- `Investigating the efficiency of custom schediling 'Affinity' and other built-in schedulings.`

## 1. What is included at this C program project
```
├── bin
├── includes
├── obj
├── out
├── res
├── scripts
└── src
    ├── affinity
    ├── loops
    ├── omplib
    └── utils
```
- `includes\: contains the basic shared .h files like data structure and global macros.`
- `res\: contains the dependent resources or generated resourcese`
- `scripts\: contains the additional scripts like auto-running or auto-ploting`
- `scr\: contains all source C files(.h/.c), also including main.c.` \
- `bin\: contains all generated executable files.`
- `obj\: contains all generated objective files.`
- `out\: contains all generated output files.`

## 2. Usage
### 1. Options
The program is designed to support different schedulings options with different macros. Therefore, we can use several flags to control which version codes are compiled:
- Without flag, the defualt serial codes are compiled.
- `-DAFFINITY`: Choose to apply user-defined 'Affinity' scheduling.
- `-DRUNTIME`: Choose to apply built-in 'Runtime' scheduling.
- `-DBEST_SCHEDULE_LOOP_1`: Choose to apply built-in 'Guided(1)' scheduling for loop1, the best scheduling is selected by other experiments.
- `-DBEST_SCHEDULE_LOOP_2`: Choose to apply built-in 'Dynamic(8)' scheduling for loop2, the best scheduling is selected by other experiments.

**Note that one can only choose one 'define' flag at one time, if no flag is specified, the serial version of the code is executed.**

### 2. Prerequisites
- Compiler: [icc](https://software.intel.com/sites/default/files/m/d/4/1/d/8/icc.txt)
- Build Tool: [make](https://www.gnu.org/software/make/)

### 3. Building
1. To compile all the avalible versions of the code use:
```sh
$ make all
```
This command firstly will create all necessary directories(obj/, bin/, out/) for the code to be executed. Then all the avalible versions of the code are compiled with all the pre-defined flags as above.\

Alternatively, one can also compile each version by hand as follows:
```sh
# firstly create necessary directories
$ make dir
# choose which version of the code to compile
$ make bin/serial -B
$ make bin/affinity -B
$ make bin/runtime -B
$ make bin/best_schedule_loop_1 -B
$ make bin/best_schedule_loop_2 -B
```
### 4.Cleaning

To clean the project run:
```sh
$ make clean
```

### 5.Running
To execute the serial code:
```sh
$ ./bin/serial
```

To execute the parallel code one has to choose the number of threads the code will be executed on. This can be done using:
```sh
$ export OMP_NUM_THREADS=$(THREADS)
```
where `$(THREADS)` is the number of threads selected.

To executed the runtime version:
```sh
$ export OMP_SCHEDULE=$(KIND,n)
$ ./bin/runtime
```
where `$(KIND,n)` is the selected scheduling option and chunksize used.

The available scheduling options are:
- `STATIC,n`: Static scheduler
- `DYNAMIC,n`: Dynamic scheduler
- `GUIDED,n`: Guided scheduler
where `n` is the selected chunksize.

### 5.Testing
```sh
$ make test
```
The program will execute the autotest.sh script and run the program by the setting at script. The result will be stored at res/ as .csv file.

```sh
$ make plot
```
Then one can plot the time line graph, efficiency graph, speedup graph... by this command. Similarly, all results will be stored at res/.
















