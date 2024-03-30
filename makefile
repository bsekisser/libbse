ARFLAGS += -U

CFLAGS += -g -Wall -MMD -MP
CFLAGS += -O2
CFLAGS += $(INCLUDE)
#CFLAGS += $(LDFLAGS)

#LDFLAGS += -Wl,-U

INCLUDE += -Iinclude

VPATH += source

OBJS = \
	callback_list.o \
	callback_qlist.o \
	dtime.o \
	mem_access.o \
	queue.o

all: libbse.a($(OBJS))

clean:
	-rm *.d *.o

clean_all: clean
	-rm *.a
