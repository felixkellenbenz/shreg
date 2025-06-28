CC=gcc
BUILDDIR=build
DEPFLAGS=-MP -MD
CODEDIRS=./src
INCDIRS=./include
CFLAGS=-g -Wall -Wextra -Wpedantic $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)

CFILES=$(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))

OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

BINARY=shreg

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

# generic rule how to make *.o files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)
