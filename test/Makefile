include ../makeinclude

all: toggle_tree dockable_group 

dockable_group: dockable_group.cxx
	$(CXX) $(CXXFLAGS) -I.. dockable_group.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

toggle_tree: toggle_tree.cxx
	$(CXX) $(CXXFLAGS) -I.. toggle_tree.cxx -L../lib -lflek_ui $(LDLIBS) -o $@

clean:
	rm -f *.o toggle_tree dockable_group

install:
