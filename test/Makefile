rootdir := ..
include $(rootdir)/util.mk

CFLAGS += -Wall -Wextra -Ofast -std=c11

CFILES := $(wildcard t*.c)
BIN := $(CFILES:%.c=%.$(CONFIG))

all: $(BIN)
run: $(BIN:%=run-%)

t%.$(CONFIG): t%.c
	@$(RUN) $(CC) $(CFLAGS) -o $@ $^
run-%: %
	@$(RUN) ./$^
