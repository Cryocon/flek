# Documentation Makefile

all:
	perl ./scandoc.pl -itemplate.pl -t4  ../Flek/*.H 
#	\
#	../Flek/Fl_App_Window.H \
#	../Flek/Fl_Stock.H \
#	../Flek/Fl_Toggle_Tree.H \
#	../Flek/Fl_Toggle_Tree_Base.H \
#	../Flek/Fl_Gl_Arcball_Window.H \
#	../Flek/Fl_Dockable_Group.H \
#	../Flek/Fl_Calendar.H ; \
#	cp ../test/arcball.cxx ./arcball.txt

sourceforge:
	scp *.txt *.html *.htm *.png jamespalmer@flek.sourceforge.net:~/flek/htdocs/docs/

install:

clean:
	rm -rf *.html *.txt

distclean: clean

depend:
