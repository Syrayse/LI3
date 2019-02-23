IDIR=../include
ODIR=obj

CC=gcc
CFLAGS = -Wall -std=c11 -g -O2 `pkg-config --cflags glib-2.0` -I$(IDIR)

DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(wildcard *.c)
SOURCES_OBJ=$(patsubst %.c,$(ODIR)/%.o,$(SOURCES))
LIBS=`pkg-config --libs glib-2.0`

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

program: $(SOURCES_OBJ)
	$(CC) $(CFLAGS) $(wildcard $(ODIR)/*.o) -o program $(LIBS)

clean:
	rm obj/*.o
	rm program