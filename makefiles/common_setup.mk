ARFLAGS += -U

BUILD_DIR ?= build
BUILD_SUBDIR = $(BUILD_DIR)$(TARGET_SUBDIR)

CFLAGS += -g -Wall -Wextra
CFLAGS += -MMD -MP
CFLAGS += -L/home/$(USER)/.local/lib
CFLAGS += $(INCLUDE)

CXXFLAGS = $(CFLAGS)

DEPS = $(DEPS_C) $(DEPS_CPP)
DEPS_C = $(filter %.d, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS_C))))
DEPS_CPP = $(filter %.d, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.cpp, $(OBJ_DIR)/%.d, $(SRCS_CPP))))

DUMP_MACHINE := $(shell $(CC) -dumpmachine)

GIT_DIR = /home/$(USER)/git

INCLUDE += $(addprefix -I,$(SRC_DIR))
INCLUDE += $(foreach DIR, $(SRC_DIR), -I$(DIR)/include)
INCLUDE += -Iinclude
INCLUDE += -I.
INCLUDE += -I$(GIT_DIR)
#INLCUDE += -Igit

LDFLAGS += -L/home/$(USER)/.local/lib

LN = ln

LNFLAGS = -sv

OBJ_DIR = $(OBJ_DIR_ROOT)/$(DUMP_MACHINE)$(TARGET_SUBDIR)
OBJ_DIR_ROOT = /srv/$(USER)/$(BUILD_DIR)/$(TARGET_NAME)

OBJS = $(OBJS_C) $(OBJS_CPP)
OBJS_C = $(filter %.o, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_C))))
OBJS_CPP = $(filter %.o, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_CPP))))

OBJ_TARGET_EXE = $(OBJ_DIR)/$(TARGET_EXE)
OBJ_TARGET_LIB_A = $(OBJ_DIR)/$(TARGET_LIB_A)
OBJ_TARGET_LIB_SO = $(OBJ_DIR)/$(TARGET_LIB_SO)

SRCS_C = $(foreach DIR, $(SRC_DIR), $(wildcard $(DIR)/*.c))
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
#$(info DEPS_CPP: $(DEPS_CPP))
#$(info INLCUDE: $(INCLUDE))
#$(info OBJ_DIR: $(OBJ_DIR))
#$(info OBJ_DIR_ROOT: $(OBJ_DIR_ROOT))
#$(info OBJS: $(OBJS))
#$(info OBJS_C: $(OBJS_C))
#$(info OBJS_CPP: $(OBJS_CPP))
#$(info SRCS: $(SRCS))
#$(info SRCS_C: $(SRCS_C))
#$(info SRCS_CPP: $(SRCS_CPP))
#$(info OBJ_TARGET_LIB_A: $(OBJ_TARGET_LIB_A))
#$(info TARGET: $(TARGET))
#$(info TARGET_EXT: $(TARGET_EXT))
#$(info TARGET_LIB_A: $(TARGET_LIB_A))
#$(info TARGET_NAME: $(TARGET_NAME))
#$(info TARGET_SUBDIR: $(TARGET_SUBDIR))
#$(info TOP_DIR: $(TOP_DIR))
