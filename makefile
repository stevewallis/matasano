CC=gcc
CFLAGS=-c -ggdb -Wall
LDFLAGS= 
SOURCES=main.c utils.c base64.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=bin/main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm bin/main
	rm *.o
	