ifdef NDEBUG
  ndebug=-DNDEBUG
else
  ndebug=
endif

sources = dictionary.h dictionary.c d_run.c makefile README

dictionary.o:
	gcc -g -c dictionary.c
	
d_run: 
	gcc d_run.c -o d_run dictionary.o

all:	clean dictionary.o d_run	
clean:
	/bin/rm -f *.o *.txt~ *.c~ *.h~ d_run

install:
	make clean
	make all
	make zip

zip:
	/bin/rm -rf dicSource
	mkdir dicSource
	cp $(sources) dicSource/
	tar cvf p12214763.tar dicSource
	/bin/rm -f p12214763.tar.gz
	gzip p12214763.tar
	/bin/rm -rf dicSource