BIN = triad_omp_c triad_omp_mem_c triad_omp_sched_c
OMPBIN = $(BIN) $(BIN:%=%.clang)
ALLBIN = $(OMPBIN)
MAIN = main.c
OMPPROC = omp_proc.c

all: $(ALLBIN)

FLAGS = -Wall -Wextra -Ofast -std=c11
XLC = xlc -qsmp=omp -qoffload -qarch=pwr9 -qtune=pwr9
CLANG = clang-gpu -Wall -Wextra -march=native -Rpass=loop-vectorize

$(ALLBIN): $(MAIN)
$(OMPBIN): $(OMPPROC)

triad_omp_c: triad_omp_c.in
	$(XLC) $(FLAGS) -o $@ $(MAIN) $(OMPPROC)

triad_omp_mem_c: triad_omp_mem_c.in
	$(XLC) $(FLAGS) -DDEVICE_MEMORY -o $@ $(MAIN) $(OMPPROC)

triad_omp_sched_c: triad_omp_mem_c.in
	$(XLC) $(FLAGS) -DMANUAL_SCHEDULE -o $@ $(MAIN) $(OMPPROC)

triad_omp_c.clang: triad_omp_c.in
	module load clang/coral-2018.08.08 && \
	$(CLANG) $(FLAGS)  -o $@ $(MAIN) $(OMPPROC)

triad_omp_mem_c.clang: triad_omp_mem_c.in
	module load clang/coral-2018.08.08 && \
	$(CLANG) $(FLAGS) -DDEVICE_MEMORY -o $@ $(MAIN) $(OMPPROC)

triad_omp_sched_c.clang: triad_omp_mem_c.in
	module load clang/coral-2018.08.08 && \
	$(CLANG) $(FLAGS) -DMANUAL_SCHEDULE -o $@ $(MAIN) $(OMPPROC)
