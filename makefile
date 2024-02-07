CFLAGS += -g -Wall -MMD -MP
CFLAGS += -O2
CFLAGS += $(INCLUDE)

INCLUDE += -I.

VPATH += source

all: include.a

clean:
	-rm *.d *.o

clean_all: clean
	-rm *.a

include.a: include.a( \
	callback_list.o \
	callback_qlist.o \
	dtime.o \
	mem_access.o \
	queue.o)
