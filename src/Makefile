CORECPPFILES = \
	fArcball.cxx \
	fVector.cxx \

UICPPFILES = \
	Fl_App_Window.cxx \
	Fl_Better_Window.cxx \
	Fl_Calendar.cxx \
	Fl_Dockable_Group.cxx \
	Fl_Stock.cxx \
	Fl_Toggle_Node_Base.cxx \
	Fl_Toggle_Node.cxx \
	Fl_Toggle_Tree_Base.cxx \
	Fl_Toggle_Tree.cxx \
	Flv_CStyle.cxx \
	Flv_Style.cxx \
	Flv_List.cxx \
	Flv_Table.cxx \
	Flve_Check_Button.cxx \
	Flve_Input.cxx \
	Flve_Combo.cxx

GLCPPFILES = \
	gl.cxx \
	Fl_Gl_Arcball_Window.cxx \

#	Fl_Dir.cxx \
#	Fl_Frametab.cxx \
#	Fl_NSlider.cxx \
#	Fl_Pix_Box.cxx \
#	Fl_Pix_Button.cxx
#	Fl_Pack_Fu.cxx \
#       Fl_File_Dialog.cxx \
#	Fl_Input_File.cxx \

CFILES = 

CLEAN =

################################################################

include ../makeinclude

all:	corelib uilib gllib

CORELIBRARY = ../lib/$(LIBNAMECORE)
COREDSONAME = $(DSOLIBNAMECORE)$(DSOEXT)
COREOBJECTS = $(CORECPPFILES:.cxx=.o) $(CORECFILES:.c=.o)
$(CORELIBRARY).a: $(COREOBJECTS)
	rm -f $@
	$(LIBCOMMAND) $@ $(COREOBJECTS)
	$(RANLIB) $@
libflek_core.so.1 libflek_core.sl.1: $(COREOBJECTS)
	$(DSOCOMMAND) $@ $(COREOBJECTS)

UILIBRARY = ../lib/$(LIBNAMEUI)
UISONAME = $(DSOLIBNAMEUI)$(DSOEXT)
UIOBJECTS = $(UICPPFILES:.cxx=.o) $(UICFILES:.c=.o)
$(UILIBRARY).a: $(UIOBJECTS)
	rm -f $@
	$(LIBCOMMAND) $@ $(UIOBJECTS)
	$(RANLIB) $@
libflek_ui.so.1 libflek_ui.sl.1: $(UIOBJECTS)
	$(DSOCOMMAND) $@ $(UIOBJECTS)

GLLIBRARY = ../lib/$(LIBNAMEGL)
GLDSONAME = $(DSOLIBNAMEGL)$(DSOEXT)
GLOBJECTS = $(GLCPPFILES:.cxx=.o) $(GLCFILES:.c=.o)
$(GLLIBRARY).a: $(GLOBJECTS)
	rm -f $@
	$(LIBCOMMAND) $@ $(GLOBJECTS)
	$(RANLIB) $@
libflek_gl.so.1 libflek_gl.sl.1: $(GLOBJECTS)
	$(DSOCOMMAND) $@ $(GLOBJECTS)

corelib: $(CORELIBRARY).a $(COREDSONAME)
uilib: $(UILIBRARY).a $(UIDSONAME)
gllib: $(GLLIBRARY).a $(GLDSONAME)

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

install: $(CORELIBRARY).a $(UILIBRARY).a $(GLLIBRARY).a $(DSONAME)
	@echo "Installing libraries..."
	@-mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIBNAMECORE)
	@rm -f $(libdir)/$(LIBNAMEUI)
	@rm -f $(libdir)/$(LIBNAMEGL)
	@-cp $(CORELIBRARY).a $(libdir)
	@-cp $(UILIBRARY).a $(libdir)
	@-cp $(GLLIBRARY).a $(libdir)
	@-chmod 644 $(libdir)/$(LIBNAMECORE).a
	@-chmod 644 $(libdir)/$(LIBNAMEUI).a
	@-chmod 644 $(libdir)/$(LIBNAMEGL).a
	@if test -n "$(DSOEXT)"; then \
		@echo "Installing core library."; \
		if test $(DSONAMECORE) = $(LIBNAMECORE).so.1; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(LIBNAMECORE)$$ext.1;\
		rm -f $(libdir)/$(LIBNAMECORE)$$ext;\
		cp $(LIBNAMECORE)$$ext.2 $(libdir); \
		chmod 755 $(libdir)/$(LIBNAMECORE)$$ext.1; \
		ln -s $(libdir)/$(LIBNAMECORE)$$ext.2 $(libdir)/$(LIBNAMECORE)$$ext;\
		@echo "Installing UI library."; \
		if test $(DSONAMEUI) = $(LIBNAMEUI).so.1; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(LIBNAMEUI)$$ext.1;\
		rm -f $(libdir)/$(LIBNAMEUI)$$ext;\
		cp $(LIBNAMEUI)$$ext.2 $(libdir); \
		chmod 755 $(libdir)/$(LIBNAMEUI)$$ext.1; \
		ln -s $(libdir)/$(LIBNAMEUI)$$ext.2 $(libdir)/$(LIBNAMEUI)$$ext;\
		@echo "Installing GL library."; \
		if test $(DSONAMEGL) = $(LIBNAMEGL).so.1; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(LIBNAMEGL)$$ext.1;\
		rm -f $(libdir)/$(LIBNAMEGL)$$ext;\
		cp $(LIBNAMEGL)$$ext.2 $(libdir); \
		chmod 755 $(libdir)/$(LIBNAMEGL)$$ext.1; \
		ln -s $(libdir)/$(LIBNAMEGL)$$ext.2 $(libdir)/$(LIBNAMEGL)$$ext;\
	fi
	@echo "Installing include files..."
	@-mkdir -p $(includedir)
	@-mkdir -p $(includedir)/Flek
	@-cp ../Flek/*.[Hh]  $(includedir)/Flek
	@-chmod 755 $(includedir)/Flek
	@-chmod 644 $(includedir)/Flek/*
	@-cp ../flek-config $(bindir)

################################################################
# DO NOT DELETE
