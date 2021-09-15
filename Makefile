CC=gcc
CFLAGS=-I. -O3 -fPIC
DEPS=librippr.h
LIBS=-lxcb
OBJS=librippr.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

librippr.so: $(OBJS)
	$(CC) -shared -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:
	clean

clean:
	rm *.o
	rm librippr.so