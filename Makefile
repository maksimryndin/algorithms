# Compiler, Linker Defines
CC      = gcc
CFLAGS  = -ansi
CFDEBUG = -ansi -pedantic -Wall -g -DDEBUG

# Source, Executable, Includes
INCLUDE   = -I include
SRC    = src
BUILD    = build
TARGET = bin/sort

SOURCES = $(shell find $(SRC) -type f -name *.c)
OBJECTS = $(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.c=.o))


# Link object files to create main executable
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) $^ -o $(TARGET) 


# Compile and Assemble C Source Files into Object Files
$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(BUILD)
	@echo " Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

# Create a gdb/dbx Capable Executable with DEBUG flags turned on
debug:
	$(CC) $(CFDEBUG) $(SRC)

# Clean Up Objects, Exectuables, Dumps out of source directory
.PHONY: clean
clean:
	@echo " Cleaning...";
	rm -f $(BUILD)/*.o $(TARGET)

# TODO Tester
