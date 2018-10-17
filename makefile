CFLAGS=-Wall -Wextra
PWD := $(shell pwd)

principal: msg.cc joueur.o
	g++ $(CFLAGS) -c joueur.cc
	g++ $(CFLAGS) -o msg joueur.o msg.cc

#clean:
#	rm -f $(PWD)/
