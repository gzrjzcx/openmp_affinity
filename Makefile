MF=	Makefile

# set compiler command: icc ...
CC = icc
CCFLAGS = -O3 -qopenmp -std=c99
CCFLAGS += -Wall
LIB = -lm 
DEFINE = 

# set various paths
SRC = src
OBJ = obj
BIN = bin
RES = res
OUT = out
SCRIPTS = scripts
INC = includes

AFF = $(SRC)/affinity
LOO = $(SRC)/loops
OMP = $(SRC)/omplib
UTI = $(SRC)/utils

SCN = $(SCRIPTS)/new

INCLUDES += -I$(INC) -I$(AFF) -I$(LOO) -I$(OMP) -I$(UTI)

VPATH = $(SRC) $(AFF) $(LOO) $(OMP) $(UTI)

MAIN_OBJ = $(OBJ)/main.o
AFF_OBJ = $(OBJ)/affinity.o
LOO_OBJ = $(OBJ)/workload.o
OMP_OBJ = $(OBJ)/omplib.o
UTI_OBJ = $(OBJ)/mem.o

# set executable name
AFFINITY = affinity
SERIAL = serial
RUNTIME = runtime
BSL1 = best_schedule_loop_1
BSL2 = best_schedule_loop_2

## dir: create all necessary directories
.PHONY: dir
dir:
	@mkdir -p $(OBJ) $(BIN) $(OUT)

## clean: clean all directories
.PHONY: clean
clean:
	@rm -rf $(OBJ) $(BIN) $(OUT)

# here is the make command, and using different flag to compile
.PHONY: all
all: dir
	@make $(BIN)/$(SERIAL) -B
	@make $(BIN)/$(AFFINITY) DEFINE=-DAFFINITY -B
	@make $(BIN)/$(RUNTIME) DEFINE=-DRUNTIME -B
	@make $(BIN)/$(BSL1) DEFINE=-DBEST_SCHEDULE_LOOP_1 -B
	@make $(BIN)/$(BSL2) DEFINE=-DBEST_SCHEDULE_LOOP_2 -B


$(OBJ)/%.o: %.c
	$(CC) $(CCFLAGS) $(DEFINE) $(INCLUDES) -o $@ -c $<

$(BIN)/$(SERIAL): $(OMP_OBJ) $(UTI_OBJ) $(LOO_OBJ) $(AFF_OBJ) $(MAIN_OBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LIB)

$(BIN)/$(AFFINITY): $(OMP_OBJ) $(UTI_OBJ) $(LOO_OBJ) $(AFF_OBJ) $(MAIN_OBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LIB)

$(BIN)/$(RUNTIME): $(OMP_OBJ) $(UTI_OBJ) $(LOO_OBJ) $(AFF_OBJ) $(MAIN_OBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LIB)

$(BIN)/$(BSL1): $(OMP_OBJ) $(UTI_OBJ) $(LOO_OBJ) $(AFF_OBJ) $(MAIN_OBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LIB)

$(BIN)/$(BSL2): $(OMP_OBJ) $(UTI_OBJ) $(LOO_OBJ) $(AFF_OBJ) $(MAIN_OBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LIB)

# Automatically Running Script to test
.PHONY: test
test:
	chmod u+x $(SCRIPTS)/autotest.sh
	./$(SCRIPTS)/autotest.sh

.PHONY: backend_test
backend_test:
	chmod u+x $(SCRIPTS)/autotest.sh
	chmod u+x $(SCRIPTS)/autotest_backend.pbs
	qsub ./$(SCRIPTS)/autotest_backend.pbs

.PHONY: plot
plot:
	python $(SCRIPTS)/plot.py


























