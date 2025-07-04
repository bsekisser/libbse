# setup

OBJ_TARGET_EXE = $(OBJ_DIR)/$(TARGET_EXE)

TARGET_EXE = $(TARGET)

include git/libbse/makefiles/common_setup.mk

# recipies

.PHONY: all
all: $(TARGET_EXE) $(DUMP_MACHINE)

.PHONY: clean_all
clean_all: clean_exe

$(TARGET_EXE): $(OBJ_TARGET_EXE) | $(OBJ_DIR)
	@[ -L $@ ] || $(LN) $(LNFLAGS) $<

$(OBJ_TARGET_EXE): $(OBJS) | $(OBJ_DIR)

#

include git/libbse/makefiles/common_build.mk
