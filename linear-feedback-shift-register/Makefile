UNAME_S := $(shell uname -s)
CC=gcc
LD=gcc
CFLAGS=-ggdb -Wall -std=c99
LDFLAGS=

ifeq ($(UNAME_S), Darwin)
	MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes --dsymutil=yes
endif

ifeq ($(UNAME_S), Linux)
	MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes
endif

BIT_OPS_OBJS = bit_ops.o test_bit_ops.o
BIT_OPS_PROG = bit_ops

LFSR_OBJS = lfsr.o test_lfsr.o bit_ops.o
LFSR_PROG = lfsr

BINARIES=$(BIT_OPS_PROG) $(LFSR_PROG)

all: $(BINARIES)

$(BIT_OPS_PROG): $(BIT_OPS_OBJS)
	$(CC) $(CFLAGS) -g -o $(BIT_OPS_PROG) $(BIT_OPS_OBJS) $(LDFLAGS)

$(LFSR_PROG): $(LFSR_OBJS)
	$(CC) $(CFLAGS) -g -o $(LFSR_PROG) $(LFSR_OBJS) $(LDFLAGS)

lfsr.c: lfsr.h
test_lfsr.c: lfsr.h

bit_ops.c: bit_ops.h
test_bit_ops.c: bit_ops.h

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	-rm -rf core *.o *~ "#"*"#" Makefile.bak $(BINARIES) *.dSYM
