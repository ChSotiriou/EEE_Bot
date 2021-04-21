CC=g++
CFLAGS=-g -Wall $(shell pkg-config --cflags --libs opencv) -Iinc

SRC=src
OBJ=obj
BINDIR=bin

BIN=$(BINDIR)/shapeDetector
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

RM=rm

all:$(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ)/* $(BINDIR)/*

print:
	echo $(OBJS)