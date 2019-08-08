rootdir := .
include $(rootdir)/util.mk

BIN := triad_omp_c triad_omp_mem_c triad_omp_sched_c
OMPBIN := $(BIN:%=%.$(CONFIG))
ALLBIN := $(OMPBIN)
MAIN := main.c
OMPPROC := omp_proc.c

all: $(ALLBIN)
run: $(ALLBIN:%=run-%)

CFLAGS += -Wall -Wextra -Ofast -std=c11

$(ALLBIN): $(MAIN)
$(OMPBIN): $(OMPPROC)

triad_omp_c.$(CONFIG): triad_omp_c.in
	@$(RUN) $(CC) $(CFLAGS) -o $@ $(MAIN) $(OMPPROC)

triad_omp_mem_c.$(CONFIG): triad_omp_mem_c.in
	@$(RUN) $(CC) $(CFLAGS) -DDEVICE_MEMORY -o $@ $(MAIN) $(OMPPROC)

triad_omp_sched_c.$(CONFIG): triad_omp_mem_c.in
	@$(RUN) $(CC) $(CFLAGS) -DMANUAL_SCHEDULE -o $@ $(MAIN) $(OMPPROC)

run-%: %
	@$(RUN) ./$^ $(ARGS)
