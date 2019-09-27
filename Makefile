CC = g++
CFLAGS = -Wall -std=c++11

BIN = bin
OBJ = obj
SRC = src

EXECUTABLES = bin_Ncomp geo_Ncomp

HEADERS = $(wildcard $(SRC)/*.h)
DEPENDENCIES = $(HEADERS:$(SRC)/%.h=$(OBJ)/%.o)

EXECUTABLE_FILES = $(EXECUTABLES:%=$(BIN)/%)

build: $(EXECUTABLE_FILES)

clean:
	-rm -r -f $(BIN) $(OBJ)

.PHONY: build clean

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

$(EXECUTABLE_FILES): $(BIN)/%: $(OBJ)/%.o $(DEPENDENCIES) | $(BIN)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful!"

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CC) $(CFLAGS) -o $@ -c $<
