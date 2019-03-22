all: triad_omp_c

triad_omp_c: triad_omp_c.in
triad_omp_c: triad_omp_c.c
	xlc-gpu -Wall -Wextra -qarch=pwr9 -qtune=pwr9 -Ofast -std=c11 -o $@ $<