# openmp_affinity
using OpenMP to parallelize the given code with user-defined 'affinity' scheduling.

This is a practical project for how to finish a real coursework, there are three main objects about this project:
- `How to construct/re-construct a real C program project.`
- `How to use Makefile to do auto testing, including frontend and backend(CIRRUS)`
- `Investigating the efficiency of custom schediling 'Affinity' and other built-in schedulings.`

### what is included at this C program project
├── build // webpack配置文件 ├── config // 项目打包路径 ├── elm // 上线项目文件，放在服务器即可正常访问