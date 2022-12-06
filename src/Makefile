IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR)

OUTDIR=..

ODIR=obj
LDIR=../lib

LIBS=-lm

_DEPS = vliaddition.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = vliaddition.o vli_source.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/VLIProgram: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)