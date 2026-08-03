CXX = g++
CC  = gcc
LD  = ld

CFLAGS_COMMON = -m32 -march=i386 -c -O2 \
                -ffreestanding \
                -fno-pic -fno-pie \
                -mno-sse -mno-mmx -mno-80387 \
                -fno-stack-protector \
                -fno-builtin \
                -ffunction-sections \
                -fdata-sections \
                -Wall \
                -Wextra \
                -I./include

CXXFLAGS = $(CFLAGS_COMMON) -fno-rtti -fno-exceptions
CFLAGS   = $(CFLAGS_COMMON) -std=c99

LDFLAGS = -m elf_i386 -T linker.ld --oformat binary --gc-sections -e _start -s

BUILD_DIR = build
OBJ_DIR   = $(BUILD_DIR)/obj
TARGET    = $(BUILD_DIR)/desktop.kde

# Sadece main.cpp (veya C kaynakları) kalsın, ekstra objeleri şimdilik bağlamıyoruz
CPP_SRCS = examples/desktop/main.cpp
C_SRCS   = 

OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(CPP_SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)
	@echo "[DEDK Build] Basarili: $(TARGET)"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean