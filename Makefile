CC = gcc
CCFLAGS = -W -Wall

PATH_SOURCES = Sources

BINARY = image-viewer
SOURCES = $(shell find $(PATH_SOURCES) -name "*.c")

all:
	$(CC) $(CCFLAGS) $(SOURCES) -o $(BINARY)

clean:
	rm -f $(BINARY)

