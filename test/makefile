CFLAGS += -g -Wall -Wextra
CFLAGS += -MMD -MP
CFLAGS += -O2
CFLAGS += -I../include


# check/verify build
OBJS = \
	alubox_switch_case.o \
	shift_roll_32.o \
	shift_roll_l.o \
	test_headers.o \
	test.o

# individual tests
TESTS = test.o \
	mem_access_test.o \
	shift_roll_test_32.o \
	shift_roll_test_64.o \
	test_bitfield.o

all: $(OBJS) test

clean:
	-rm $(OBJS) $(TESTS) *.d test

test: test.o $(TESTS) | all

.PHONY: test_test
test_test: test
	./test

-include *.d
