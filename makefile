CC=gcc
CFLAGS=-c -ggdb -Wall
LDFLAGS= 
SOURCES=main.c utils.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=bin/main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm bin/main
	rm main.o utils.o
	