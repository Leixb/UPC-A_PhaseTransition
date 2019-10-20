CC = g++
CFLAGS = -Wall -std=c++11

BIN = bin
OBJ = obj
SRC = src

EXECUTABLES = main

HEADERS = $(wildcard $(SRC)/*.h)
DEPENDENCIES = $(HEADERS:$(SRC)/%.h=$(OBJ)/%.o)

EXECUTABLE_FILES = $(EXECUTABLES:%=$(BIN)/%)

build: $(EXECUTABLE_FILES)

clean:
	-rm -r -f $(BIN) $(OBJ)

.PHONY: build clean plots

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

$(EXECUTABLE_FILES): $(BIN)/%: $(OBJ)/%.o $(DEPENDENCIES) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful!"
	@echo "Run: \"make plots\" to generate the plots"

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CC) $(CFLAGS) -o $@ -c $<

plots: bin/main
	bash makePlots.sh 10 25 50 60 80 100 150
