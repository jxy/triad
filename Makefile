BIN = triad_omp_c triad_omp_mem_c triad_omp_sched_c
all: $(BIN) $(BIN:%=%.clang)

FLAGS = -Wall -Wextra -Ofast -std=c11
XLC = xlc -qsmp=omp -qoffload -qarch=pwr9 -qtune=pwr9
CLANG = clang-gpu -Wall -Wextra -march=native -Rpass=loop-vectorize

triad_omp_c: triad_omp_c.in
triad_omp_c: triad_omp_c.c
	$(XLC) $(FLAGS) -o $@ $<

triad_omp_mem_c: triad_omp_mem_c.in
triad_omp_mem_c: triad_omp_c.c
	$(XLC) $(FLAGS) -DDEVICE_MEMORY -o $@ $<

triad_omp_sched_c: triad_omp_mem_c.in
triad_omp_sched_c: triad_omp_c.c
	$(XLC) $(FLAGS) -DMANUAL_SCHEDULE -o $@ $<

triad_omp_c.clang: triad_omp_c.in
triad_omp_c.clang: triad_omp_c.c
	$(CLANG) $(FLAGS)  -o $@ $<

triad_omp_mem_c.clang: triad_omp_mem_c.in
triad_omp_mem_c.clang: triad_omp_c.c
	$(CLANG) $(FLAGS) -DDEVICE_MEMORY -o $@ $<

triad_omp_sched_c.clang: triad_omp_mem_c.in
triad_omp_sched_c.clang: triad_omp_c.c
	$(CLANG) $(FLAGS) -DMANUAL_SCHEDULE -o $@ $<
