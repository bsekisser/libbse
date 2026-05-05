export CFLAGS += -O2

export SRC_DIR = source

TARGETs = libbse.a libbse.so


include makefiles/common.mk


.PHONY: test
test:
	$(MAKE) -C test test_test
