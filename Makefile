CC = g++
LIBS = -L../fir1 -lfir_static
FIR1 = ../fir1/Fir1.cpp ../fir1/Fir1.h

_SRC = sox.cpp Fir1.cpp audioio.cpp
SRC = $(patsubst %,$(LIBS)/%,$(_SRC))

OBJS = Fir1.o main.o audioio.o

.PHONY: all

all: audioio.o Fir1.o main.o main.out clean

audioio.o: ../audioio/audioio.h
	$(CC) -o ../audioio/audioio.cxx ../audioio/audioio.h 

Fir1.o: $(FIR1)
	$(CC) $(FIR1) $(LIBS)

main.o: main.cpp
	$(CC) -c main.cpp

main.out: $(objects)
	$(CC) $(OBJS)

.PHONY: clean

clean:
	rm $(OBJS)
