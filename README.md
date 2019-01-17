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
- `includes\: contains the basic shared .h files like data structure and global macro.`
- `res\: contains the dependent resources or generated resourcese`
- `scripts\: contains the additional scripts like auto-running or auto-ploting`
- `scr\: contains all source C files(.h/.c), also including main.c.` \
- `bin\: contains all generated executable files.`
- `obj\: contains all generated objective files.`
- `out\: contains all generated output files.`

## 2. How to build
