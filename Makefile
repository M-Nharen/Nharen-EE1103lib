# ============================================
#  Nharen-EE1103lib — Simple Makefile
#  Builds static library libee1103.a in repo root
# ============================================

# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99 -Iinclude
LDFLAGS := -lm

# Directories and files
SRC_DIR := src
INC_DIR := include
OBJ     := $(SRC_DIR)/*.o
LIB     := libee1103.a

# Default target
all: $(LIB)

# Build static library (.a)
$(LIB): $(SRC_DIR)/*.c
	@echo "Compiling source files..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/*.c
	@echo "Archiving into static library..."
	ar rcs $(LIB) *.o
	@rm -f *.o
	@echo "✅ Build complete: $(LIB) created in current folder."

# Clean up
clean:
	rm -f $(SRC_DIR)/*.o *.o $(LIB)
	@echo "🧹 Clean complete."

.PHONY: all clean
