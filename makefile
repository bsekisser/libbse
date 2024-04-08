TOP_DIR = $(PWD)
GIT_DIR = $(TOP_DIR)/..

ARFLAGS += -U

CFLAGS += -g -Wall -Wextra
CFLAGS += -O2 -march=native
CFLAGS += -MMD -MP
CFLAGS += $(INCLUDE)

INCLUDE += -Iinclude
INCLUDE += -I$(GIT_DIR)

SRC_DIR = source
OBJ_DIR = build-$(shell $(CC) -dumpmachine)

VPATH += source

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))

.SECONDARY: $(OBJS)

all: libbse.a($(OBJS)) | $(OBJ_DIR)

#$(OBJ_DIR)/%.o: $(OBJS)
#	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJ_DIR):
	-mkdir -p $(OBJ_DIR)

clean:
	-rm $(OBJ_DIR)/*.d $(OBJ_DIR)/*.o

clean_all: clean
	-rm -r $(OBJ_DIR) *.a

#-include $(OBJ_DIR)/*.d
-include $(DEPS)
