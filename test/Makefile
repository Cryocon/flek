include ../makeinclude

all: ftest arcball stock_buttons dockable_group toggle_tree # frametab pixbutton slider 

ftest: ftest.cxx
	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. ftest.cxx -L../lib -lflek_ui $(LDLIBS) -lGL -lGLU -o $@

arcball: arcball.cxx
	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. arcball.cxx -L../lib -lflek_ui $(LDLIBS) -lGL -lGLU -o $@

stock_buttons: stock_buttons.cxx
	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. stock_buttons.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

wtest: wtest.cxx
	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. wtest.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

wtest2: wtest2.cxx
	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. wtest2.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#packfu: packfu.cxx
#	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. packfu.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

dockable_group: dockable_group.cxx
	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. dockable_group.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

toggle_tree: toggle_tree.cxx
	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. toggle_tree.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#filedialog: filedialog.cxx
#	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. filedialog.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#frametab: frametab.cxx
#	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. frametab.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#pixbutton: pixbutton.cxx
#	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. pixbutton.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#slider: slider.cxx
#	$(CXX) $(CXXFLAGS) $(FLTKINC) -I.. slider.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

clean:
	rm -f core *.o toggle_tree dockable_group bitmaps filedialog \
	arcball frametab pixbutton slider pixbutton packfu wtest wtest2 stock_buttons 

install:
