CFLAGS += -O2
CFLAGS += -fPIC

LDFLAGS += -shared

SRC_DIR = source
SRCS = $(wildcard $(SRC_DIR)/*.c)

TARGET_LIB = libbse
TARGET_LIB_A = $(TARGET_LIB).a
TARGET_LIB_SO = $(TARGET_LIB).so

.PHONY: all
all: $(TARGET_LIB_SO)

include makefile.setup

$(OBJ_TARGET_LIB_SO): $(OBJ_TARGET_LIB_A)

$(TARGET_LIB_SO): $(TARGET_LIB_A)

include makefile.build
