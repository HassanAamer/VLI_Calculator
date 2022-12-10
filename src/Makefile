IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall

EXECDIR=../bin

ODIR=obj
LDIR=../lib

LIBS=-lm

_DEPS = vli_addition.h vli_parser.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = vli_addition.o vli_calculator.o vli_parser.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECDIR)/VLIcalculator: $(OBJ)
	@mkdir -p $(EXECDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)