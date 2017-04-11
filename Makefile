CFLAGS = -Wall -W -pedantic -std=c99
VPATH = src

ifndef BMFS_RELEASE
CFLAGS += -g -O2
else
CFLAGS += -O3
endif

.PHONY: all
all: bmfs dir-test disk-test

ifndef NO_FUSE
all: bmfs-fuse
endif

bmfs: bmfs.c libbmfs.a

dir-test: dir-test.c libbmfs.a

disk-test: disk-test.c libbmfs.a

entry.o: entry.c entry.h

dir.o: dir.c dir.h entry.h

disk.o: disk.c disk.h dir.h entry.h limits.h

libbmfs.a: disk.o dir.o entry.o
	$(AR) $(ARFLAGS) $@ $^

bmfs-fuse: bmfs-fuse.c libbmfs.a
bmfs-fuse: LDLIBS += $(shell pkg-config --libs fuse)
bmfs-fuse: CFLAGS += $(shell pkg-config --cflags fuse)
bmfs-fuse: CFLAGS += -std=gnu99

libbmfs.o: libbmfs.c libbmfs.h

.PHONY: clean
clean:
	$(RM) bmfs bmfs-fuse
	$(RM) libbmfs.a
	$(RM) disk.o dir.o entry.o

