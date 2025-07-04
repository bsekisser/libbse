ARFLAGS += -U

BUILD_DIR = build

CFLAGS += -g -Wall -Wextra
CFLAGS += -MMD -MP
CFLAGS += $(INCLUDE)

CXXFLAGS = $(CFLAGS)

DEPS = $(DEPS_C) $(DEPS_CPP)
DEPS_C = $(filter %.d, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS_C))))
DEPS_CPP = $(filter %.d, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.cpp, $(OBJ_DIR)/%.d, $(SRCS_CPP))))

DUMP_MACHINE := $(shell $(CC) -dumpmachine)

GIT_DIR = $(TOP_DIR)/git

INCLUDE += -I$(TOP_DIR)
INCLUDE += $(foreach DIR, $(SRC_DIR), -I$(DIR))
INCLUDE += $(foreach DIR, $(SRC_DIR), -I$(DIR)/include)
INCLUDE += -Iinclude
INCLUDE += -I$(GIT_DIR)
INCLUDE += -Igit

LN = ln

LNFLAGS = -sv

OBJ_DIR = /build/$(USER)/$(TARGET)/$(DUMP_MACHINE)

OBJS = $(OBJS_C) $(OBJS_CPP)
OBJS_C = $(filter %.o, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_C))))
OBJS_CPP = $(filter %.o, $(foreach DIR, $(SRC_DIR), $(patsubst $(DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_CPP))))

SRCS_C = $(foreach DIR, $(SRC_DIR), $(wildcard $(DIR)/*.c))
SRCS_CPP = $(foreach DIR, $(SRC_DIR), $(wildcard $(DIR)/*.cpp))


TOP_DIR = $(PWD)

VPATH += $(SRC_DIR)
