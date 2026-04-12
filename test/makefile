CFLAGS += -g -Wall -Wextra
CFLAGS += -MMD -MP
CFLAGS += -O2
CFLAGS += -I../include


# check/verify build
OBJS = \
	alubox_switch_case.o \
	bitops.o \
	shift_roll_32.o \
	shift_roll_64.o \
	shift_roll_l.o \
	shift_roll.o \
	test_headers.o \
	test.o

# individual tests
TESTS = test.o \
	mem_access_test.o \
	test_bitfield.o \
	test_bitops32.o \
	test_shift_roll_32.o \
	test_shift_roll_64.o

all: $(OBJS) test

clean:
	-rm $(OBJS) $(TESTS) *.d test

test: test.o $(TESTS) | all

.PHONY: test_test
test_test: test
	./test

-include *.d
