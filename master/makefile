CC=g++
CFLAGS=-g -Wall
RM=rm -rf

DEF=-DDEBUG
LD=-l wiringPi
LIB=lib
INC=-I lib/ultrasonic -I lib/pi2c -I lib/drive

BIN=main
SRC=main.cpp 
OBJ=pi2c.o ultrasonic.o drive.o

all: $(BIN)

$(BIN): $(SRC) $(OBJ)
	$(CC) $(CFLAGS) $(DEF) $(LD) $(INC) $^ -o $@

pi2c.o: $(LIB)/pi2c/pi2c.cpp 
	$(CC) $(CFLAGS) $(DEF) -c $^ -o $@

ultrasonic.o: $(LIB)/ultrasonic/ultrasonic.cpp
	$(CC) $(CFLAGS) $(LD) $(DEF) -c $(INC) $^ -o $@

drive.o: $(LIB)/drive/drive.cpp
	$(CC) $(CFLAGS) $(LD) $(DEF) -c $(INC) $^ -o $@

clean:
	$(RM) *.o

reset: clean
	$(RM) $(BIN)
	
