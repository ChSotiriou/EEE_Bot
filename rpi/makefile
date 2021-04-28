CC=g++
CFLAGS=-g -Wall $(shell pkg-config --cflags --libs opencv) -l wiringPi -Iinc

SRC=src
OBJ=obj
BINDIR=bin

BIN=$(BINDIR)/lineFollow
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

rebuild:clean all
