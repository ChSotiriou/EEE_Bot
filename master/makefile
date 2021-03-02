CC=g++
CFLAGS=-g -Wall
RM=rm -rf

# DEF=-DDEBUG
LD=-l wiringPi
LIB=lib
INC=-I lib/ultrasonic -I lib/pi2c -I lib/drive -I lib/pid
BUILD=bin

BIN=main
SRC=main.cpp 
OBJ=$(BUILD)/pi2c.o $(BUILD)/ultrasonic.o $(BUILD)/drive.o $(BUILD)/pid.o

all: $(BIN)

$(BIN): $(SRC) $(OBJ)
	$(CC) $(CFLAGS) $(DEF) $(LD) $(INC) $^ -o $@

$(BUILD)/pi2c.o: $(LIB)/pi2c/pi2c.cpp 
	$(CC) $(CFLAGS) $(DEF) -c $^ -o $@

$(BUILD)/ultrasonic.o: $(LIB)/ultrasonic/ultrasonic.cpp
	$(CC) $(CFLAGS) $(LD) $(DEF) -c $(INC) $^ -o $@

$(BUILD)/drive.o: $(LIB)/drive/drive.cpp
	$(CC) $(CFLAGS) $(LD) $(DEF) -c $(INC) $^ -o $@
	
$(BUILD)/pid.o: $(LIB)/pid/pid.cpp
	$(CC) $(CFLAGS) $(LD) $(DEF) -c $(INC) $^ -o $@

clean:
	$(RM) $(BUILD)/*.o

reset: clean
	$(RM) $(BIN)
	
