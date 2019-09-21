CC = g++
CFLAGS = -Wall
DEPS = src/graph.h src/graph_generator.h
OBJ = obj/graph.o obj/graph_generator.o

.PHONY: all clean

all: bin/binomial_stats bin/binomial_1case

obj/%.o: src/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

bin/%: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ src/$(@F).cpp

clean:
	-rm obj/*.o
