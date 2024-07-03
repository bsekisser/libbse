CFLAGS += -O2

SRC_DIR = source
SRCS = $(wildcard $(SRC_DIR)/*.c)

TARGET_LIB = libbse.a

.PHONY: all
all: $(TARGET_LIB)

include makefile.setup
include makefile.build
