IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR)

OUTDIR=..

ODIR=obj
LDIR=../lib

LIBS=-lm

_DEPS = vli_addition.h vli_reader.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = vli_addition.o vli_calculator.o vli_reader.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/VLIcalculator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)