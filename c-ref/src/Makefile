IDIR=../include
ODIR=obj
LDIR=lib
OLDIR=$(ODIR)/lib
DOCDIR=docs

CC=gcc
CFLAGS = -Wall -ansi -g -Ofast `pkg-config --cflags glib-2.0` -I$(IDIR)

DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(wildcard *.c)
MY_LIBS=$(wildcard $(LDIR)/*.c)
SOURCES_OBJ=$(patsubst %.c,$(ODIR)/%.o,$(SOURCES))
MY_LIBS_OBJ=$(foreach o, $(patsubst %.c,%.o,$(MY_LIBS)), $(ODIR)/$o)

LIBS=`pkg-config --libs glib-2.0`

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

program: $(SOURCES_OBJ) $(MY_LIBS_OBJ)
	$(CC) $(CFLAGS) $(wildcard $(ODIR)/*.o) $(wildcard $(OLDIR)/*.o) -o program $(LIBS)

clean:
	rm -rf $(ODIR)/*.o
	rm -rf $(ODIR)/$(LDIR)/*.o
	rm -rf program
	rm -rf $(DOCDIR)/*

doc:
	doxygen Doxyfile