CC=g++
CFLAGS=-Wall -Werror -g -pedantic $(OTHERFLAGS)
TARGET = test

SOURCES = implement_hex_board.cpp
OBJS = $(SOURCES:.cpp=.o)
FILES = *.asm *.i *.o *.d

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<  -o $@

$(TARGET).out: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.PHONY: compile-all
compile-all: $(OBJS) $(TARGET).out
	
.PHONY: build
build: $(TARGET).out
	
.PHONY: clean
clean:
	rm -f $(FILES) $(TARGET).out