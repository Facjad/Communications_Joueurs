PWD := $(shell pwd)

principal: msg.cc joueur.o
	g++ -Wall -c joueur.cc
	g++ -Wall -o msg joueur.o msg.cc

#clean:
#	rm -f $(PWD)/
