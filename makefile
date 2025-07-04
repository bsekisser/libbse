export CFLAGS += -O2

export SRC_DIR = source

export TARGET = libbse

include makefiles/common_setup.mk

.PHONY: all
all:
	$(MAKE) -f makefiles/build_liba.mk all
	$(MAKE) -f makefiles/build_libso.mk all

include makefiles/common.mk
