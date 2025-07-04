# setup

OBJ_TARGET_LIB_A = $(OBJ_DIR)/$(TARGET_LIB_A)

TARGET_LIB = $(TARGET)

TARGET_LIB_A = $(TARGET_LIB).a

include git/libbse/makefiles/common_setup.mk

# recipies

.PHONY: all
all: $(TARGET_LIB_A) $(DUMP_MACHINE)

.PHONY: clean_all
clean_all: clean_liba

$(TARGET_LIB_A): $(OBJ_TARGET_LIB_A) | $(OBJ_DIR)
	@[ -L $@ ] || $(LN) $(LNFLAGS) $<

$(OBJ_TARGET_LIB_A): $(OBJ_TARGET_LIB_A)($(OBJS)) | $(OBJ_DIR)

#

include git/libbse/makefiles/common_build.mk
