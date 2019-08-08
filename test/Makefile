rootdir := ..
include $(rootdir)/util.mk

CFLAGS += -Wall -Wextra -Ofast -std=gnu11

CFILES := $(wildcard t*.c)
BIN := $(CFILES:%.c=b/%.$(CONFIG))

all: $(BIN)
run: $(BIN:b/%=run-%)

b/t%.$(CONFIG): t%.c
	@$(RUN) $(CC) $(CFLAGS) -o $@ $^
run-%: b/%
	@$(RUN) ./$^
