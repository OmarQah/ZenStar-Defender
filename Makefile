#quick compiler to show rendering is working as expected will make final cmake once done
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Ihal/include `sdl2-config --cflags`

# Linker flags
LDFLAGS = `sdl2-config --libs` -lSDL2_image

# Source files
SRCS = app/src/main.c \
       hal/src/assets.c \
       hal/src/input.c \
       hal/src/entities.c \
       hal/src/renderer.c \
       hal/src/collisions.c

# Output executable
TARGET = spacegame

# Build rule
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET)
