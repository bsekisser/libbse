# setup

CFLAGS += -fPIC

LDFLAGS += -shared

OBJ_TARGET_LIB_SO = $(OBJ_DIR)/$(TARGET_LIB_SO)

TARGET_LIB = $(TARGET)

TARGET_LIB_SO = $(TARGET_LIB).so

include git/libbse/makefiles/common_setup.mk

# recipies

.PHONY: all
all: $(TARGET_LIB_SO) $(DUMP_MACHINE)

.PHONY: clean_all
clean_all: clean_libso

$(TARGET_LIB_SO): $(OBJ_TARGET_LIB_SO) | $(OBJ_DIR)
	@[ -L $@ ] || $(LN) $(LNFLAGS) $<

$(OBJ_TARGET_LIB_SO): $(OBJ_TARGET_LIB_SO)($(OBJS)) | $(OBJ_DIR)

#

include git/libbse/makefiles/common_build.mk
