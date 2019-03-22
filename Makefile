all: triad_omp_c triad_omp_mem_c

triad_omp_c: triad_omp_c.in
triad_omp_c: triad_omp_c.c
	xlc-gpu -Wall -Wextra -qarch=pwr9 -qtune=pwr9 -Ofast -std=c11 -o $@ $<

triad_omp_mem_c: triad_omp_mem_c.in
triad_omp_mem_c: triad_omp_c.c
	xlc-gpu -DDEVICE_MEMORY -Wall -Wextra -qarch=pwr9 -qtune=pwr9 -Ofast -std=c11 -o $@ $<
