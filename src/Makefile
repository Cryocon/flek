#  -*- sh -*-

# Note:  In order for the rpm script to work the last line in H_FLEK_* must not 
# have any trailing spaces!

CPP_FLEK_CORE = \
	FDate.cxx \
	FSocket.cxx \
	FFile.cxx \
	FVector.cxx \
	FImage.cxx \
	FSGI.cxx \
	FPNM.cxx

H_FLEK_CORE = \
	FBase.H \
	FSocket.H \
	FDate.H \
	FFile.H \
	FImage.H \
	FMatrix3x3.H \
	FMatrix4x4.H \
	FPNM.H \
	FQuaternion.H \
	FSGI.H \
	FTransformation.H \
	FVector.H \
	FVector2.H \
	FVector3.H \
	FVector4.H \
	math.H \
	iostream.H \
	types.H      

CPP_FLEK_XML = \
	FXml.cxx \

H_FLEK_XML = \
	FXml.H

CPP_FLEK_JPEG = \
	FJPEG.cxx \

H_FLEK_JPEG = \
	FJPEG.H

CPP_FLEK_UI = \
	Fl_App_Window.cxx \
	Fl_Better_Window.cxx \
	Fl_Calendar.cxx \
	Fl_Dockable_Window.cxx \
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

H_FLEK_UI = \
	Fl_App_Window.H \
	Fl_Better_Window.H \
	Fl_Calendar.H \
	Fl_Dockable_Window.H \
	Fl_Stock.H \
	Fl_Toggle_Node_Base.H \
	Fl_Toggle_Node.H \
	Fl_Toggle_Tree_Base.H \
	Fl_Toggle_Tree.H \
	Flv_CStyle.H \
	Flv_Style.H \
	Flv_List.H \
	Flv_Table.H \
	Flve_Check_Button.H \
	Flve_Input.H \
	Flve_Combo.H

CPP_FLEK_GL = \
	gl.cxx \
	FArcball_Control.cxx \
	Fl_Gl_Arcball_Window.cxx 

H_FLEK_GL = \
	gl.H \
	FArcball_Control.H \
	FDolly_Control.H \
	FZoom_Control.H \
	FTrans_Control.H \
	Fl_Gl_Arcball_Window.H

################################################################

include ../makeinclude

ALL = flek-core
INSTALL = flek-core-install

ifdef FLTK_LIB
	ALL += flek-ui
	INSTALL += flek-ui-install
endif

ifdef JPEG_LIB
	ALL += flek-jpeg
	INSTALL += flek-jpeg-install
endif

ifdef GL_LIB
	ALL += flek-gl
	INSTALL += flek-gl-install
endif

ifdef XML_LIB
	ALL += flek-xml
	INSTALL += flek-xml-install
endif

all: $(ALL)

install: $(INSTALL)

################################################################

LIB_FLEK_CORE = ../lib/$(LIB_NAME_FLEK_CORE)
DSO_FLEK_CORE = ../lib/$(DSO_NAME_FLEK_CORE)$(DSOEXT)
OBJ_FLEK_CORE = $(CPP_FLEK_CORE:.cxx=.o) 
$(LIB_FLEK_CORE).a: $(OBJ_FLEK_CORE)
	rm -f $@
	mkdir -p ../lib
	$(LIB_COMMAND) $@ $(OBJ_FLEK_CORE)
	$(RANLIB) $@
../lib/libflek_core.so.1 ../lib/libflek_core.sl.1: $(OBJ_FLEK_CORE)
	$(DSO_COMMAND) ../lib/$@ $(OBJ_FLEK_CORE)

LIB_FLEK_UI = ../lib/$(LIB_NAME_FLEK_UI)
DSO_FLEK_UI = ../lib/$(DSO_NAME_FLEK_UI)$(DSOEXT)
OBJ_FLEK_UI = $(CPP_FLEK_UI:.cxx=.o) 
$(LIB_FLEK_UI).a: $(OBJ_FLEK_UI)
	rm -f $@
	mkdir -p ../lib
	$(LIB_COMMAND) $@ $(OBJ_FLEK_UI)
	$(RANLIB) $@
../lib/libflek_ui.so.1 ../lib/libflek_ui.sl.1: $(OBJ_FLEK_UI)
	$(DSO_COMMAND) ../lib/$@ $(OBJ_FLEK_UI)

LIB_FLEK_GL = ../lib/$(LIB_NAME_FLEK_GL)
DSO_FLEK_GL = ../lib/$(DSO_NAME_FLEK_GL)$(DSOEXT)
OBJ_FLEK_GL = $(CPP_FLEK_GL:.cxx=.o) 
$(LIB_FLEK_GL).a: $(OBJ_FLEK_GL)
	rm -f $@
	mkdir -p ../lib
	$(LIB_COMMAND) $@ $(OBJ_FLEK_GL)
	$(RANLIB) $@
../lib/libflek_gl.so.1 ../lib/libflek_gl.sl.1: $(OBJ_FLEK_GL)
	$(DSO_COMMAND) ../lib/$@ $(OBJ_FLEK_GL)

LIB_FLEK_XML = ../lib/$(LIB_NAME_FLEK_XML)
DSO_FLEK_XML = ../lib/$(DSO_NAME_FLEK_XML)$(DSOEXT)
OBJ_FLEK_XML = $(CPP_FLEK_XML:.cxx=.o) 
$(LIB_FLEK_XML).a: $(OBJ_FLEK_XML)
	rm -f $@
	mkdir -p ../lib
	$(LIB_COMMAND) ../lib/$@ $(OBJ_FLEK_XML)
	$(RANLIB) $@
../lib/libflek_xml.so.1 ../lib/libflek_xml.sl.1: $(OBJ_FLEK_XML)
	$(DSO_COMMAND) ../lib/$@ $(OBJ_FLEK_XML)

LIB_FLEK_JPEG = ../lib/$(LIB_NAME_FLEK_JPEG)
DSO_FLEK_JPEG = ../lib/$(DSO_NAME_FLEK_JPEG)$(DSOEXT)
OBJ_FLEK_JPEG = $(CPP_FLEK_JPEG:.cxx=.o) 
$(LIB_FLEK_JPEG).a: $(OBJ_FLEK_JPEG)
	rm -f $@
	mkdir -p ../lib
	$(LIB_COMMAND) ../lib/$@ $(OBJ_FLEK_JPEG)
	$(RANLIB) $@
../lib/libflek_jpeg.so.1 ../lib/libflek_jpeg.sl.1: $(OBJ_FLEK_JPEG)
	$(DSO_COMMAND) ../lib/$@ $(OBJ_FLEK_JPEG)

flek-core: $(LIB_FLEK_CORE).a $(DSO_FLEK_CORE)
flek-ui: $(LIB_FLEK_UI).a $(DSO_FLEK_UI)
flek-gl: $(LIB_FLEK_GL).a $(DSO_FLEK_GL)
flek-xml: $(LIB_FLEK_XML).a $(DSO_FLEK_XML)
flek-jpeg: $(LIB_FLEK_JPEG).a $(DSO_FLEK_JPEG)

################################################################

.SUFFIXES:	.cxx .h .o

.cxx.o :
	$(CXX) -I.. $(XML_INC) $(JPEG_INC) $(GL_INC) $(FLTK_INC) $(CXXFLAGS) -c $< -o $(<:.cxx=.o)
.c.o :
	$(CC) -I. $(CFLAGS) -c -o $@ $<

################################################################

clean :
	-@ rm -f *.o *.do *~ ../include/*~ makedepend o
	-@ rm -rf ../lib

distclean: clean
	-@ rm -f config.* makeinclude

depend:
	$(MAKEDEPEND) $(CXXFLAGS) -I. $(CPPFILES) > makedepend

################################################################

flek-core-install: $(LIB_FLEK_CORE).a $(DSO_FLEK_CORE)
	@echo "Installing libflek_core..."
	@-mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIB_NAME_FLEK_CORE)
	@-cp $(LIB_FLEK_CORE).a $(libdir)
	@-chmod 644 $(libdir)/$(LIB_NAME_FLEK_CORE).a
	@if test -n "$(DSOEXT)"; then \
		echo "Installing libflek_core DSO library."; \
		if test $(DSO_FLEK_CORE) = ../lib/$(DSO_NAME_FLEK_CORE).so.1; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(DSO_NAME_FLEK_CORE)$$ext.1;\
		rm -f $(libdir)/$(DSO_NAME_FLEK_CORE)$$ext;\
		cp $(DSO_FLEK_CORE) $(libdir); \
		chmod 755 $(libdir)/$(DSO_NAME_FLEK_CORE)$$ext.1; \
		ln -s $(libdir)/$(DSO_NAME_FLEK_CORE)$$ext.1 $(libdir)/$(DSO_NAME_FLEK_CORE)$$ext;\
	fi
	@echo "Installing include files..."
	@-mkdir -p $(includedir)
	@-mkdir -p $(includedir)/Flek
	@-cd ../Flek/; cp $(H_FLEK_CORE) $(includedir)/Flek; cd ../src/
	@-chmod 755 $(includedir)/Flek
	@-chmod 644 $(includedir)/Flek/*
	@-mkdir -p $(bindir)
	@-chmod 755 $(bindir)
	cp ../flek-config $(bindir)/

flek-ui-install: $(LIB_FLEK_UI).a $(DSO_FLEK_UI)
	@echo "Installing libflek_UI..."
	@-mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIB_NAME_FLEK_UI)
	@-cp $(LIB_FLEK_UI).a $(libdir)
	@-chmod 644 $(libdir)/$(LIB_NAME_FLEK_UI).a
	@if test -n "$(DSOEXT)"; then \
		echo "Installing libflek_ui DSO library."; \
		if test $(DSO_FLEK_UI) = ../lib/$(DSO_NAME_FLEK_UI).so.1; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(DSO_NAME_FLEK_UI)$$ext.1;\
		rm -f $(libdir)/$(DSO_NAME_FLEK_UI)$$ext;\
		cp $(DSO_FLEK_UI) $(libdir); \
		chmod 755 $(libdir)/$(DSO_NAME_FLEK_UI)$$ext.1; \
		ln -s $(libdir)/$(DSO_NAME_FLEK_UI)$$ext.1 $(libdir)/$(DSO_NAME_FLEK_UI)$$ext;\
	fi
	@echo "Installing include files..."
	@-mkdir -p $(includedir)
	@-mkdir -p $(includedir)/Flek
	@-cd ../Flek/; cp $(H_FLEK_UI) $(includedir)/Flek; cd ../src/
	@-chmod 755 $(includedir)/Flek
	@-chmod 644 $(includedir)/Flek/*

flek-gl-install: $(LIB_FLEK_GL).a $(DSO_FLEK_GL)
	@echo "Installing libflek_gl..."
	@-mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIB_NAME_FLEK_GL)
	@-cp $(LIB_FLEK_GL).a $(libdir)
	@-chmod 644 $(libdir)/$(LIB_NAME_FLEK_GL).a
	@if test -n "$(DSOEXT)"; then \
		echo "Installing libflek_gl DSO library."; \
		if test $(DSO_FLEK_GL) = ../lib/$(DSO_NAME_FLEK_GL).so.1; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(DSO_NAME_FLEK_GL)$$ext.1;\
		rm -f $(libdir)/$(DSO_NAME_FLEK_GL)$$ext;\
		cp $(DSO_FLEK_GL) $(libdir); \
		chmod 755 $(libdir)/$(DSO_NAME_FLEK_GL)$$ext.1; \
		ln -s $(libdir)/$(DSO_NAME_FLEK_GL)$$ext.1 $(libdir)/$(DSO_NAME_FLEK_GL)$$ext;\
	fi
	@echo "Installing include files..."
	@-mkdir -p $(includedir)
	@-mkdir -p $(includedir)/Flek
	@-cd ../Flek/; cp $(H_FLEK_GL) $(includedir)/Flek; cd ../src/
	@-chmod 755 $(includedir)/Flek
	@-chmod 644 $(includedir)/Flek/*

flek-xml-install: $(LIB_FLEK_XML).a $(DSO_FLEK_XML)
	@echo "Installing libflek_xml..."
	@-mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIB_NAME_FLEK_XML)
	@-cp $(LIB_FLEK_XML).a $(libdir)
	@-chmod 644 $(libdir)/$(LIB_NAME_FLEK_XML).a
	@if test -n "$(DSOEXT)"; then \
		echo "Installing libflek_xml DSO library."; \
		if test $(DSO_FLEK_XML) = ../lib/$(DSO_NAME_FLEK_XML).so.1; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(DSO_NAME_FLEK_XML)$$ext.1;\
		rm -f $(libdir)/$(DSO_NAME_FLEK_XML)$$ext;\
		cp $(DSO_FLEK_XML) $(libdir); \
		chmod 755 $(libdir)/$(DSO_NAME_FLEK_XML)$$ext.1; \
		ln -s $(libdir)/$(DSO_NAME_FLEK_XML)$$ext.1 $(libdir)/$(DSO_NAME_FLEK_XML)$$ext;\
	fi
	@echo "Installing include files..."
	@-mkdir -p $(includedir)
	@-mkdir -p $(includedir)/Flek
	@-cd ../Flek/; cp $(H_FLEK_XML) $(includedir)/Flek; cd ../src/
	@-chmod 755 $(includedir)/Flek
	@-chmod 644 $(includedir)/Flek/*

flek-jpeg-install: $(LIB_FLEK_JPEG).a $(DSO_FLEK_JPEG)
	@echo "Installing libflek_jpeg..."
	@-mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIB_NAME_FLEK_JPEG)
	@-cp $(LIB_FLEK_JPEG).a $(libdir)
	@-chmod 644 $(libdir)/$(LIB_NAME_FLEK_JPEG).a
	@if test -n "$(DSOEXT)"; then \
		echo "Installing libflek_jpeg DSO library."; \
		if test $(DSO_FLEK_JPEG) = ../lib/$(DSO_NAME_FLEK_JPEG).so.1; then ext=.so; else ext=.s1; fi; \
		rm -f $(libdir)/$(DSO_NAME_FLEK_JPEG)$$ext.1;\
		rm -f $(libdir)/$(DSO_NAME_FLEK_JPEG)$$ext;\
		cp $(DSO_FLEK_JPEG) $(libdir); \
		chmod 755 $(libdir)/$(DSO_NAME_FLEK_JPEG)$$ext.1; \
		ln -s $(libdir)/$(DSO_NAME_FLEK_JPEG)$$ext.1 $(libdir)/$(DSO_NAME_FLEK_JPEG)$$ext;\
	fi
	@echo "Installing include files..."
	@-mkdir -p $(includedir)
	@-mkdir -p $(includedir)/Flek
	@-cd ../Flek/; cp $(H_FLEK_JPEG) $(includedir)/Flek; cd ../src/
	@-chmod 755 $(includedir)/Flek
	@-chmod 644 $(includedir)/Flek/*

################################################################

list-headers:
	@echo "Generating header file lists."
	@echo "$(H_FLEK_CORE)" | sed 's/[ ]*$$//' | sed 's/ / =/g' | tr '=' "\n" | sed 's/^/\%\{prefix\}\/include\/Flek\//g' > flek_core_h.list
	@echo "$(H_FLEK_XML)"  | sed 's/[ ]*$$//' | sed 's/ / =/g' | tr '=' "\n" | sed 's/^/\%\{prefix\}\/include\/Flek\//g' > flek_xml_h.list
	@echo "$(H_FLEK_JPEG)"  | sed 's/[ ]*$$//' | sed 's/ / =/g' | tr '=' "\n" | sed 's/^/\%\{prefix\}\/include\/Flek\//g' > flek_jpeg_h.list
	@echo "$(H_FLEK_UI)"   | sed 's/[ ]*$$//' | sed 's/ / =/g' | tr '=' "\n" | sed 's/^/\%\{prefix\}\/include\/Flek\//g' > flek_ui_h.list
	@echo "$(H_FLEK_GL)"   | sed 's/[ ]*$$//' | sed 's/ / =/g' | tr '=' "\n" | sed 's/^/\%\{prefix\}\/include\/Flek\//g' > flek_gl_h.list

################################################################
# DO NOT DELETE
