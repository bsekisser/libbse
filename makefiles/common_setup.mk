ARFLAGS += -U

BUILD_DIR ?= build
BUILD_SUBDIR = $(BUILD_DIR)$(TARGET_SUBDIR)

CFLAGS += -g -Wall -Wextra
CFLAGS += -MMD -MP
CFLAGS += -Wunused-result
CFLAGS += -Wunused-value
CFLAGS += -L/home/$(USER)/.local/lib
CFLAGS += $(INCLUDE)

CXXFLAGS = $(CFLAGS)

DEPS = $(DEPS_C) $(DEPS_CC) $(DEPS_CPP)
DEPS_C = $(filter %.d, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.c, $(OBJ_DIR)/%.c.d, $(SRCS_C))))
DEPS_CC = $(filter %.d, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.cc, $(OBJ_DIR)/%.cc.d, $(SRCS_CC))))
DEPS_CPP = $(filter %.d, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.cpp, $(OBJ_DIR)/%.cpp.d, $(SRCS_CPP))))

DUMP_MACHINE := $(shell $(CC) -dumpmachine)

INCLUDE += $(addprefix -I,$(SRC_DIR))
INCLUDE += $(foreach DIR, $(SRC_DIR), -I$(DIR)/include)
INCLUDE += -Iinclude
INCLUDE += -I.
INCLUDE += -I$(GIT_DIR)

LDFLAGS += -L/home/$(USER)/.local/lib

LN = ln

LNFLAGS = -sv

OBJ_DIR = $(OBJ_DIR_ROOT)/$(DUMP_MACHINE)$(TARGET_SUBDIR)
OBJ_DIR_ROOT = /srv/$(USER)/$(BUILD_DIR)/$(TARGET_NAME)

OBJS = $(OBJS_C) $(OBJS_CC) $(OBJS_CPP)
OBJS_C = $(filter %.o, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.c, $(OBJ_DIR)/%.c.o, $(SRCS_C))))
OBJS_CC = $(filter %.o, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.cc, $(OBJ_DIR)/%.cc.o, $(SRCS_CC))))
OBJS_CPP = $(filter %.o, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.cpp, $(OBJ_DIR)/%.cpp.o, $(SRCS_CPP))))

OBJ_TARGET_EXE = $(OBJ_DIR)/$(TARGET_EXE)
OBJ_TARGET_LIB_A = $(OBJ_DIR)/$(TARGET_LIB_A)
OBJ_TARGET_LIB_SO = $(OBJ_DIR)/$(TARGET_LIB_SO)

SRCS_C = $(foreach DIR, $(SRC_DIR), $(wildcard $(DIR)/*.c))
SRCS_CC = $(foreach DIR, $(SRC_DIR), $(wildcard $(DIR)/*.cc))
SRCS_CPP = $(foreach DIR, $(SRC_DIR), $(wildcard $(DIR)/*.cpp))

TARGET_EXE = $(TARGET_NAME).exe
TARGET_EXT = $(patsubst .%,%,$(suffix $(TARGET)))
TARGET_LIB_A = $(TARGET_NAME).a
TARGET_LIB_SO = $(TARGET_NAME).so
TARGET_NAME = $(basename $(TARGET))
TARGET_SUBDIR = $(patsubst %,/%,$(TARGET_EXT))

#TOP_DIR = $(CWD)

VPATH += $(SRC_DIR)

#

#$(info DEPS: $(DEPS))
#$(info DEPS_C: $(DEPS_C))
#$(info DEPS_CC: $(DEPS_CC))
#$(info DEPS_CPP: $(DEPS_CPP))
#$(info INLCUDE: $(INCLUDE))
#$(info OBJ_DIR: $(OBJ_DIR))
#$(info OBJ_DIR_ROOT: $(OBJ_DIR_ROOT))
#$(info OBJS: $(OBJS))
#$(info OBJS_C: $(OBJS_C))
#$(info OBJS_CC: $(OBJS_CC))
#$(info OBJS_CPP: $(OBJS_CPP))
#$(info SRCS: $(SRCS))
#$(info SRCS_C: $(SRCS_C))
#$(info SRCS_CC: $(SRCS_CC))
#$(info SRCS_CPP: $(SRCS_CPP))
#$(info OBJ_TARGET_LIB_A: $(OBJ_TARGET_LIB_A))
#$(info TARGET: $(TARGET))
#$(info TARGET_EXT: $(TARGET_EXT))
#$(info TARGET_LIB_A: $(TARGET_LIB_A))
#$(info TARGET_NAME: $(TARGET_NAME))
#$(info TARGET_SUBDIR: $(TARGET_SUBDIR))
#$(info TOP_DIR: $(TOP_DIR))
