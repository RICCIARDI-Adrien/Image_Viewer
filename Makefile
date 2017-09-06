CC = gcc
CCFLAGS = -W -Wall

PATH_INCLUDES = Includes
PATH_SOURCES = Sources

BINARY = image-viewer
INCLUDES = -I$(PATH_INCLUDES)
LIBRARIES = -lSDL2 -lSDL2_image
SOURCES = $(shell find $(PATH_SOURCES) -name "*.c")

all:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) -o $(BINARY) $(LIBRARIES)

clean:
	rm -f $(BINARY)

