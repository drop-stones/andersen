
CC  := clang
CXX := clang++
LLVM_FLAG := -S -emit-llvm -fno-discard-value-names

SRC_FILES := $(wildcard ./*.c)
LLVM_IR_FILES := $(SRC_FILES:%.c=%.ll)

# do not generate file command
.PHONY: all clean

all: $(LLVM_IR_FILES)

./%.ll: ./%.c Makefile
	$(CC) $(LLVM_FLAG) $<

clean:
	rm -rf $(LLVM_IR_FILES)
