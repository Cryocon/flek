# Documentation Makefile

all:
	perl ./scandoc.pl -itemplate.pl -t4 ../Flek/*.H ../src/*.cxx
	cp ../test/arcball.cxx ./arcball.txt
	cp ../AUTHORS ./authors.txt

sourceforge:
	scp *.txt *.html *.htm *.png *.gif jamespalmer@flek.sourceforge.net:~/flek/htdocs/docs/

install:

clean:
	rm -rf *.html *.txt

distclean: clean

depend:
