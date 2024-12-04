# Compiler
CC = gcc

# Executable name
TARGET = bin/a.out

# Source and include directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRCS = $(shell find $(SRC_DIR) -name '*.c')

# Object files (build directory + source file name with .o extension)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Detect the operating system
ifeq ($(OS), Windows_NT)
    # Windows-specific settings
    INCLUDES = -I$(INC_DIR)
    
    DYN_LIBS = 

    STATIC_LIBS = -lglew32 -lglfw3 -lopengl32 -lgdi32 -lglu32

    LDFLAGS = -L/ucrt64/lib -Wl,-Bdynamic $(DYN_LIBS) -Wl,-Bstatic $(STATIC_LIBS) -mwindows
else
    # Linux-specific settings
    INCLUDES = -I$(INC_DIR)
    LIBS = -lGLEW -lglfw -lGL -lGLU -lX11 -lm
    LDFLAGS = $(LIBS)
endif

# Compiler flags
CFLAGS = $(INCLUDES) -Wall -Wextra -O2

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Rule to compile source files into object files (with new paths)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build files
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

# Run the program
run: $(BIN_DIR)
	cd $(BIN_DIR) && ./a.out

# Rebuild the project
rebuild: clean all

# Debug compiler flags
CFLAGS_DEBUG = $(CFLAGS) -g

# Debug build
CFLAGS_DEBUG = $(INCLUDES) -Wall -Wextra -g

debug: clean
	$(MAKE) CFLAGS="$(CFLAGS_DEBUG)" all
