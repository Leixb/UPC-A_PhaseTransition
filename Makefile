CC = g++
CFLAGS = -Wall -std=c++11

DEPS = src/graph.h src/graph_generator.h
OBJ = obj/graph.o obj/graph_generator.o
BIN = bin/binomial_stats bin/binomial_1case bin/geometric_1case

.PHONY: all clean
.SECONDARY: $(OBJ)

all: $(BIN)

obj/%.o: src/%.cpp $(DEPS) | obj
	$(CC) $(CFLAGS) -c -o $@ $<

bin/%: $(OBJ) | bin
	$(CC) $(CFLAGS) -o $@ $^ src/$(@F).cpp

bin:
	mkdir -p bin

obj:
	mkdir -p obj

clean:
	-rm bin/* obj/*
