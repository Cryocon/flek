include ../makeinclude

all: stock_buttons dockable_group toggle_tree # frametab pixbutton slider

stock_buttons: stock_buttons.cxx
	$(CXX) $(CXXFLAGS) -I.. stock_buttons.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

wtest: wtest.cxx
	$(CXX) $(CXXFLAGS) -I.. wtest.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

wtest2: wtest2.cxx
	$(CXX) $(CXXFLAGS) -I.. wtest2.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#packfu: packfu.cxx
#	$(CXX) $(CXXFLAGS) -I.. packfu.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

dockable_group: dockable_group.cxx
	$(CXX) $(CXXFLAGS) -I.. dockable_group.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

toggle_tree: toggle_tree.cxx
	$(CXX) $(CXXFLAGS) -I.. toggle_tree.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#filedialog: filedialog.cxx
#	$(CXX) $(CXXFLAGS) -I.. filedialog.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#frametab: frametab.cxx
#	$(CXX) $(CXXFLAGS) -I.. frametab.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#pixbutton: pixbutton.cxx
#	$(CXX) $(CXXFLAGS) -I.. pixbutton.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

#slider: slider.cxx
#	$(CXX) $(CXXFLAGS) -I.. slider.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

clean:
	rm -f core *.o toggle_tree dockable_group bitmaps filedialog \
	frametab pixbutton slider pixbutton packfu wtest wtest2 stock_buttons 

install:
