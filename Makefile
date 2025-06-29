CC=gcc
BUILD_DIR=./build/
DEP_FLAGS=-MP -MD
SRC_DIR=./src/
INCLUDE_DIR=./include/
CFLAGS=-g -Wall -Wextra -Wpedantic $(foreach D,$(INCLUDE_DIR),-I$(D)) $(DEP_FLAGS)

C_FILES=$(foreach D, $(SRC_DIR), $(wildcard $(D)*.c))

OBJECTS=$(patsubst %.c,$(BUILD_DIR)%.o,$(C_FILES))
DEPFILES=$(patsubst %.c,$(BUILD_DIR)%.d,$(C_FILES))

BINARY=shreg

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

# generic rule how to make *.o files
$(BUILD_DIR)%.o: %.c create_build_dir
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(BINARY)

create_build_dir:
	$(foreach D, $(SRC_DIR), $(shell mkdir -p $(BUILD_DIR)$(D)))
