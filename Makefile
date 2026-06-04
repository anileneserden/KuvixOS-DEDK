# ==============================================================================
# KuvixOS DEDK V2 - Makefile
# ==============================================================================

CXX = g++
CC  = gcc
LD  = ld

CFLAGS_COMMON = -m32 -march=i386 -c -O2 -g \
                -ffreestanding \
                -fno-pie \
                -fno-PIC \
                -fno-stack-protector \
                -ffunction-sections \
                -fdata-sections \
                -fpack-struct=1 \
                -Wall \
                -Wextra \
                -I./include

CXXFLAGS = $(CFLAGS_COMMON) -fno-rtti -fno-exceptions

CFLAGS   = $(CFLAGS_COMMON)

LDFLAGS = -m elf_i386 -T linker.ld --oformat binary --gc-sections

# Klasör Yapıları
BUILD_DIR = build
OBJ_DIR   = $(BUILD_DIR)/obj
TARGET    = $(BUILD_DIR)/desktop.kde

CPP_SRCS = examples/desktop/main.cpp \
           src/graphics/Framebuffer.cpp \
           src/runtime/Runtime.cpp

C_SRCS   = src/lib/string.c

OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(CPP_SRCS)) \
       $(patsubst %.c, $(OBJ_DIR)/%.o, $(C_SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)
	@echo " "
	@echo "========================================================"
	@echo "[DEDK Build] Başarılı: $(TARGET)"
	@echo "========================================================"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	@echo "[DEDK Clean] Derleme klasörü temizlendi."

.PHONY: all clean