CC = g++
CFLAGS = -Wall -std=c++11
DEPS = src/graph.h src/graph_generator.h
OBJ = obj/graph.o obj/graph_generator.o
DIRS = bin obj

.PHONY: all clean dirs

all: dirs bin/binomial_stats bin/binomial_1case bin/geometric_1case

obj/%.o: src/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

bin/%: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ src/$(@F).cpp

dirs: $(DIRS)
	mkdir -p $(DIRS)

clean:
	-rm obj/*.o
