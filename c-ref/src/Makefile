default: doI.o validation.o
	gcc -o doI doI.o validation.o

doI.o: doI.c validation.h
	gcc -g -O -c doI.c

validation.o: validation.c validation.h
	gcc -g -O -c validation.c

clean:
	rm -rf *.o