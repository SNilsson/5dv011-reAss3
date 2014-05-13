CC = gcc
CFLAGS = -std=c99 
LDFLAGS = 
LIBS = -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = run.x

.PHONY : all clean release debug

all : $(OBJ) $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o : %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -v $(OBJ) $(TARGET)

release : CFLAGS += -DNDEBUG -O3
release : all

debug : CFLAGS += -g -Wall
debug : all

