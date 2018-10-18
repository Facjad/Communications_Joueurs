CFLAGS=-Wall -Wextra
PWD := $(shell pwd)

mesures: main_mesures.cc core
	g++ $(CFLAGS) -o mesures joueur.o routines.o main_mesures.cc

pasapas: main_pasapas.cc core
	g++ $(CFLAGS) -o pasapas joueur.o routines.o main_pasapas.cc

core: joueur.o routines.o
	g++ $(CFLAGS) -c joueur.cc
	g++ $(CFLAGS) -c routines.cc

#clean:
#	rm -f $(PWD)/
