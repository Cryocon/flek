CPPFILES = \
	Fl_App_Window.cxx \
	Fl_Dockable_Group.cxx \
	Fl_Better_Window.cxx \
	Fl_Calendar.cxx \
	Fl_Toggle_Node_Base.cxx \
	Fl_Toggle_Node.cxx \
	Fl_Toggle_Tree_Base.cxx \
	Fl_Toggle_Tree.cxx \
	Fl_Stock.cxx 
#	Fl_Dir.cxx \
#	Fl_Frametab.cxx \
#	Fl_NSlider.cxx \
#	Fl_Pix_Box.cxx \
#	Fl_Pix_Button.cxx
#	Fl_Pack_Fu.cxx \

#Fl_File_Dialog.cxx \
#	Fl_Input_File.cxx \


CFILES = 

CLEAN =

################################################################

include ../makeinclude

LIBRARY = ../lib/$(LIBNAME)
DSONAME = $(DSOLIBNAME)$(DSOEXT)

OBJECTS = $(CPPFILES:.cxx=.o) $(CFILES:.c=.o)

all: 	$(LIBRARY).a $(DSONAME)

$(LIBRARY).a: $(OBJECTS) # fl_call_main.o
	rm -f $@
	$(LIBCOMMAND) $@ $(OBJECTS)
	$(RANLIB) $@

libflek_ui.so.1 libflek_ui.sl.1: $(OBJECTS)
	$(DSOCOMMAND) $@ $(OBJECTS)

.SUFFIXES:	.cxx .h .o

.cxx.o :
	$(CXX) -I.. $(FLTKINC) $(CXXFLAGS) -c $< -o $(<:.cxx=.o)
.c.o :
	$(CC) -I. $(CFLAGS) -c -o $@ $<

clean :
	-@ rm -f *.o *.do $(LIBRARY) $(CLEAN) core *~ ../include/*~ makedepend cmap

distclean: clean
	-@ rm -f config.* makeinclude

depend:
	$(MAKEDEPEND) $(CXXFLAGS) -I. $(CPPFILES) $(CFILES) > makedepend

install: $(LIBRARY).a $(DSONAME)
	@echo "Installing libraries..."
	@-mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIBNAME)
	@-cp $(LIBRARY).a $(libdir)
	@-chmod 644 $(libdir)/$(LIBNAME).a
	@if test -n "$(DSOEXT)"; then \
		if test $(DSONAME) = $(LIBNAME).so.2; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(LIBNAME)$$ext.2;\
		rm -f $(libdir)/$(LIBNAME)$$ext;\
		cp $(LIBNAME)$$ext.2 $(libdir); \
		chmod 755 $(libdir)/$(LIBNAME)$$ext.2; \
		ln -s $(libdir)/$(LIBNAME)$$ext.2 $(libdir)/$(LIBNAME)$$ext;\
	fi
	@echo "Installing include files..."
	@-mkdir -p $(includedir)
	@-mkdir -p $(includedir)/Flek
	@-cp ../Flek/*.[Hh]  $(includedir)/Flek
	@-chmod 755 $(includedir)/Flek
	@-chmod 644 $(includedir)/Flek/*

################################################################
# DO NOT DELETE
